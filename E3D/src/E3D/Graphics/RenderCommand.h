#pragma once

#include "Program.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Mesh.h"

namespace E3D {
    class RenderCommand {
    public:
        static void Clear(float r, float g, float b, float a = 1.f);
        static void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Program& program);
        static void Draw(const VertexArray& vao, int first, int count, const Program& program);
        static void Draw(const Mesh& mesh, const Program& program);

        static void SetViewPort(int x, int y, int width, int height);
        static void SetDepthTest(bool enabled);
        static void SetCullFace(bool enabled);
        static void SetWireframeMode(bool enabled);
    };
}
