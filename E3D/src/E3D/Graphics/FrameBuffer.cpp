#include "FrameBuffer.h"

#include <iostream>

#include "glad/glad.h"

namespace E3D {
    FrameBuffer::FrameBuffer(const Specification& spec) : id(0)
                                                          , colorAttachment(0)
                                                          , depthStencilAttachment(0)
                                                          , spec(spec) {
        glGenFramebuffers(1, &id);
        Bind();

        auto internalFormat = GL_RGBA8;
        auto format = GL_RGBA;
        auto attachmentPoint = GL_COLOR_ATTACHMENT0;

        glGenTextures(1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D, colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, spec.width, spec.height, 0, format, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentPoint, GL_TEXTURE_2D, colorAttachment, 0);

        internalFormat = GL_DEPTH24_STENCIL8;
        attachmentPoint = GL_DEPTH_STENCIL_ATTACHMENT;

        glGenRenderbuffers(1, &depthStencilAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, depthStencilAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, spec.width, spec.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentPoint, GL_RENDERBUFFER, depthStencilAttachment);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "Framebuffer incomplete!" << std::endl;

        Default();
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &id);
        glDeleteTextures(1, &colorAttachment);
        glDeleteRenderbuffers(1, &depthStencilAttachment);
    }

    void FrameBuffer::BindColorTexture() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorAttachment);
    }

    void FrameBuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FrameBuffer::Default() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
