#include "Mesh.h"

namespace E3D {
    Ref<Mesh> Mesh::Create(const std::vector<float>& vertices,
                           const VertexBufferLayout& layout,
                           const std::vector<unsigned int>& indices) {
        auto mesh = CreateRef<Mesh>(InternalTag{});
        mesh->data = {
            .vertices = vertices,
            .layout = layout,
            .indices = indices,
        };

        mesh->SetupMesh();
        return mesh;
    }

    void Mesh::SetupMesh() {
        vao.Init();
        vbo.Load(data.vertices.data(), data.vertices.size() * sizeof(float));
        vao.AddBuffer(vbo, data.layout);
        ibo.Load(data.indices.data(), data.indices.size());
        VertexArray::Unbind();
    }
}
