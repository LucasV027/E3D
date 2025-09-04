#pragma once

#include <vector>

#include "glad/glad.h"

#include "VertexBufferLayout.h"
#include "E3D/Core/Base.h"

namespace E3D {
    class Buffer {
    public:
        virtual ~Buffer() {
            glDeleteBuffers(1, &handle);
        }

        GLuint Handle() const { return handle; }
        size_t Len() const { return length; }

    protected:
        template <typename T>
        void Init(const std::vector<T>& data, const GLbitfield flags = GL_DYNAMIC_STORAGE_BIT) {
            length = data.size();
            glCreateBuffers(1, &handle);
            glNamedBufferStorage(handle, data.size() * sizeof(T), data.data(), flags);
        }

    protected:
        GLuint handle = GL_NONE;
        size_t length = 0;
    };

    class VertexBuffer final : public Buffer {
    public:
        template <typename T>
        static Ref<VertexBuffer> Create(const std::vector<T>& data, const VertexBufferLayout& layout) {
            auto vb = CreateRef<VertexBuffer>();
            vb->Init(data);
            vb->layout = layout;
            return vb;
        }

        const VertexBufferLayout& Layout() const { return layout; }

    private:
        VertexBufferLayout layout;
    };

    class IndexBuffer final : public Buffer {
    public:
        static Ref<IndexBuffer> Create(const std::vector<unsigned int>& data) {
            auto ib = CreateRef<IndexBuffer>();
            ib->Init(data);
            return ib;
        }
    };
}
