#pragma once

namespace E3D {
    class FrameBuffer {
    public:
        struct Specification {
            int width = 1;
            int height = 1;
        };

    public:
        explicit FrameBuffer(const Specification& spec);
        ~FrameBuffer();

        void BindColorTexture() const;
        void Bind() const;
        static void Default();

    private:
        unsigned int id;
        unsigned int colorAttachment;
        unsigned int depthStencilAttachment;
        Specification spec;
    };
}
