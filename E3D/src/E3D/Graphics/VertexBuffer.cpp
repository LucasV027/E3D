#include "VertexBuffer.h"

#include "glad/glad.h"

namespace E3D {
    /////////////// Vertex buffer layout ///////////////
    VertexBufferLayout::VertexBufferLayout() : stride(0) {}

    VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferEntry> initEntries)
        : entries(initEntries), stride(0) {
        for (const auto& entry : entries) {
            stride += entry.GetSize();
        }
    }

    void VertexBufferLayout::Push(const AttributeType type, const unsigned int count, const bool normalized) {
        entries.push_back({type, count, normalized});
        stride += count * AttributeTypeSize(type);
    }

    unsigned int VertexBufferLayout::GetStride() const { return stride; }
    const std::vector<VertexBufferEntry>& VertexBufferLayout::GetEntries() const { return entries; }


    /////////////// Vertex buffer ///////////////
    VertexBuffer::VertexBuffer() : id(0) {}

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::Load(const void* data, const unsigned int size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
