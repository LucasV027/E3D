#include "VertexArray.h"

#include <ranges>

#include "glad/glad.h"

namespace E3D {
    VertexArray::VertexArray() : vao(0) {}

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &vao);
    }

    void VertexArray::Init() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const {
        Bind();
        vbo.Bind();

        unsigned int offset = 0;
        const auto& elements = layout.GetEntries();
        for (size_t i = 0; i < elements.size(); ++i) {
            const auto& [type, count, normalized] = elements[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                                  static_cast<int>(count),
                                  static_cast<GLenum>(type),
                                  normalized,
                                  static_cast<int>(layout.GetStride()),
                                  reinterpret_cast<const void*>(offset)
            );
            offset += count * AttributeTypeSize(type);
        }

        vbo.Unbind();
    }

    void VertexArray::Bind() const {
        glBindVertexArray(vao);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }
}
