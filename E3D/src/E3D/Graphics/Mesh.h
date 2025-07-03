#pragma once

#include <memory>
#include <vector>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace E3D {
    class Mesh {
    public:
        friend class RenderCommand;

        Mesh() = default;

        static std::unique_ptr<Mesh> Create(const std::vector<float>& vertices,
                                            const VertexBufferLayout& layout,
                                            const std::vector<unsigned int>& indices);

    private:
        void SetupMesh();

    public:
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;

        struct {
            std::vector<float> vertices;
            VertexBufferLayout layout;
            std::vector<unsigned int> indices;
        } data;
    };
}
