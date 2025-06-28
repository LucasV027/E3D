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
        static void Unbind();

    private:
        unsigned int vao;
    };
}
