#include "RenderBuffer.h"

#include "glad/glad.h"

namespace E3D {
    Ref<RenderBuffer> RenderBuffer::Create(const int width, const int height, const Type type) {
        auto rbo = CreateRef<RenderBuffer>(InternalTag{});
        rbo->width = width;
        rbo->height = height;
        rbo->type = type;

        glGenRenderbuffers(1, &rbo->id);
        rbo->Bind();

        // clang-format off
        auto internalFormat = GL_RGBA8;
        switch (rbo->type) {
        case Type::Color:        internalFormat = GL_RGBA8;              break;
        case Type::Depth:        internalFormat = GL_DEPTH_COMPONENT24;  break;
        case Type::Stencil:      internalFormat = GL_STENCIL_INDEX8;     break;
        case Type::DepthStencil: internalFormat = GL_DEPTH24_STENCIL8;   break;
        }
        // clang-format on

        glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, rbo->width, rbo->height);
        rbo->Unbind();
        return rbo;
    }

    RenderBuffer::~RenderBuffer() {
        glDeleteRenderbuffers(1, &id);
    }

    void RenderBuffer::Bind() const {
        glBindRenderbuffer(GL_RENDERBUFFER, id);
    }

    void RenderBuffer::Unbind() {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    unsigned int RenderBuffer::Id() const { return id; }
    int RenderBuffer::Width() const { return width; }
    int RenderBuffer::Height() const { return height; }
}
