#pragma once

namespace E3D {
    class IndexBuffer {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void Load(const unsigned int* data, unsigned int count);

        void Bind() const;
        static void Unbind();

        unsigned int GetCount() const;

    private:
        unsigned int id;
        unsigned int count;
    };
}
