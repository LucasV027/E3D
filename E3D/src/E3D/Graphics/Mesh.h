#pragma once

#include <vector>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "E3D/Core/Base.h"

namespace E3D {
    class Mesh : public RefOnly<Mesh> {
    public:
        explicit Mesh(InternalTag) {}
        friend class RenderCommand;

        static Ref<Mesh> Create(const std::vector<float>& vertices,
                                const VertexBufferLayout& layout,
                                const std::vector<unsigned int>& indices);

    private:
        void SetupMesh();

    private:
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;

        struct {
            std::vector<float> vertices;
            VertexBufferLayout layout;
            std::vector<unsigned int> indices;
        } data;
    };
};

