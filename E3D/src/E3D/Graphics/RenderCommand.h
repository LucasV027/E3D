#pragma once

#include "Program.h"
#include "VertexArray.h"

namespace E3D {
    class RenderCommand {
    public:
        static void Clear(float r, float g, float b, float a = 1.f);
        static void Draw(const VertexArray& vao, const Buffer& ibo, const Program& program);

        static void SetViewPort(int x, int y, int width, int height);
        static void SetDepthTest(bool enabled);
        static void SetCullFace(bool enabled);
        static void SetWireframeMode(bool enabled);
    };
}
