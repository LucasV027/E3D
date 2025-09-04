#include "FrameBuffer.h"

#include <format>
#include <stdexcept>
#include <iostream>

#include "glad/glad.h"

namespace E3D {
    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &id);
    }

    void FrameBuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    static unsigned int ToGLAttachment(const FrameBuffer::Attachment attachment) {
        switch (attachment) {
        case FrameBuffer::Attachment::Color0: return GL_COLOR_ATTACHMENT0;
        case FrameBuffer::Attachment::Color1: return GL_COLOR_ATTACHMENT1;
        case FrameBuffer::Attachment::Color2: return GL_COLOR_ATTACHMENT2;
        case FrameBuffer::Attachment::Color3: return GL_COLOR_ATTACHMENT3;
        case FrameBuffer::Attachment::Depth: return GL_DEPTH_ATTACHMENT;
        case FrameBuffer::Attachment::Stencil: return GL_STENCIL_ATTACHMENT;
        case FrameBuffer::Attachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;
        default: return 0;
        }
    }

    FrameBuffer::Builder::Builder() {
        fbo = CreateRef<FrameBuffer>(InternalTag{});
    }

    FrameBuffer::Builder& FrameBuffer::Builder::WithSize(const int width, const int height) {
        if (width <= 0 || height <= 0) {
            throw std::runtime_error(std::format(
                "FrameBuffer::WithSize: size already set to {}x{}, cannot set to {}x{}",
                fbo->width, fbo->height, width, height));
        }

        if (fbo->width != -1 && fbo->height != -1 &&
            (fbo->width != width || fbo->height != height)) {
            throw std::runtime_error(std::format("FrameBuffer::WithSize: invalid dimensions {}x{}", width, height));
        }


        fbo->width = width;
        fbo->height = height;
        return *this;
    }

    FrameBuffer::Builder& FrameBuffer::Builder::WithRenderBufferAttachment(
        const Attachment attachment,
        const Ref<RenderBuffer>& renderBuffer) {
        if (fbo->width != -1 && fbo->height != -1 &&
            fbo->width != renderBuffer->Width() || fbo->height != renderBuffer->Height()) {
            throw std::runtime_error(std::format(
                "FrameBuffer::WithRenderBufferAttachment: size mismatch (expected {}x{}, got {}x{})",
                fbo->width, fbo->height, renderBuffer->Width(), renderBuffer->Height()));
        }

        if (fbo->textureAttachments.contains(attachment) ||
            fbo->renderBufferAttachments.contains(attachment)) {
            throw std::runtime_error("FrameBuffer::WithRenderBufferAttachment: attachment slot already used.");
        }

        fbo->renderBufferAttachments[attachment] = renderBuffer;
        return *this;
    }

    FrameBuffer::Builder& FrameBuffer::Builder::WithTextureAttachment(
        const Attachment attachment,
        const Ref<Texture>& texture) {
        if (fbo->width != -1 && fbo->height != -1 &&
            fbo->width != texture->Width() || fbo->height != texture->Height()) {
            throw std::runtime_error(std::format(
                "FrameBuffer::WithTextureAttachment: size mismatch (expected {}x{}, got {}x{})",
                fbo->width, fbo->height, texture->Width(), texture->Height()));
        }

        if (fbo->textureAttachments.contains(attachment) ||
            fbo->renderBufferAttachments.contains(attachment)) {
            throw std::runtime_error("FrameBuffer::WithTextureAttachment: attachment slot already used.");
        }
        fbo->textureAttachments[attachment] = texture;
        return *this;
    }

    Ref<FrameBuffer> FrameBuffer::Builder::Build() {
        glGenFramebuffers(1, &fbo->id);
        fbo->Bind();

        for (auto& [attachment, tex] : fbo->textureAttachments) {
            glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                ToGLAttachment(attachment),
                GL_TEXTURE_2D,
                tex->Id(),
                0
            );
        }

        for (auto& [attachment, rbo] : fbo->renderBufferAttachments) {
            glFramebufferRenderbuffer(
                GL_FRAMEBUFFER,
                ToGLAttachment(attachment),
                GL_RENDERBUFFER,
                rbo->Id()
            );
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Framebuffer is incomplete!" << std::endl;
            return nullptr;
        }

        fbo->Unbind();
        return fbo;
    }
}
