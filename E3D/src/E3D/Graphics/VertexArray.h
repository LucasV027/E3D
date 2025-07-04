#pragma once

#include "VertexBuffer.h"

namespace E3D {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Init();

        void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int vao;
    };
}
