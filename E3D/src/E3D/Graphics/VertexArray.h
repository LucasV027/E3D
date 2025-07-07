#pragma once

#include "glad/glad.h"

#include "E3D/Core/Base.h"
#include "Buffer.h"

namespace E3D {
    class VertexArray {
    public:
        static Ref<VertexArray> Create(const Ref<VertexBuffer>& vbo, const Ref<IndexBuffer>& ibo) {
            auto _this = CreateRef<VertexArray>();
            _this->vbo = vbo;
            _this->ibo = ibo;

            glCreateVertexArrays(1, &_this->handle);
            glVertexArrayVertexBuffer(_this->handle, 0, vbo->Handle(), 0, vbo->Layout().GetStride());
            glVertexArrayElementBuffer(_this->handle, ibo->Handle());

            const auto& entries = vbo->Layout().GetEntries();
            for (size_t i = 0; i < entries.size(); ++i) {
                const auto& [type, count, normalized, offset] = entries[i];

                glEnableVertexArrayAttrib(_this->handle, i);
                glVertexArrayAttribFormat(_this->handle, i, count, static_cast<GLenum>(type), normalized, offset);
                glVertexArrayAttribBinding(_this->handle, i, 0);
            }

            return _this;
        }

        VertexArray() = default;
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

    private:
        GLuint handle = GL_NONE;
        Ref<VertexBuffer> vbo;
        Ref<IndexBuffer> ibo;
    };
}
