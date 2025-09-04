#pragma once

#include "E3D/Core/Base.h"

namespace E3D {
    class RenderBuffer : RefOnly<RenderBuffer> {
    public:
        enum class Type {
            Color, Depth, Stencil, DepthStencil
        };

        explicit RenderBuffer(InternalTag) {};
        static Ref<RenderBuffer> Create(int width, int height, Type type);

        ~RenderBuffer();
        void Bind() const;
        void Unbind();

        unsigned int Id() const;
        int Width() const;
        int Height() const;

    private:
        unsigned int id = 0;
        int width = 0;
        int height = 0;
        Type type = Type::DepthStencil;
    };
}
