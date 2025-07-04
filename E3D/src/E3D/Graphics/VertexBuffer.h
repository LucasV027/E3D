#pragma once

#include <vector>
#include <initializer_list>

#include "glad/glad.h"

namespace E3D {
    enum class AttributeType {
        Byte = GL_BYTE,
        UnsignedByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        UnsignedInt = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
        Double = GL_DOUBLE
    };

    constexpr unsigned int AttributeTypeSize(const AttributeType type) {
        switch (type) {
        case AttributeType::Byte: return 1;
        case AttributeType::UnsignedByte: return 1;
        case AttributeType::Short: return 2;
        case AttributeType::UnsignedShort: return 2;
        case AttributeType::Int: return 4;
        case AttributeType::UnsignedInt: return 4;
        case AttributeType::Float: return 4;
        case AttributeType::Double: return 8;
        }
        return 0;
    }

    struct VertexBufferEntry {
        AttributeType type;
        unsigned int count;
        bool normalized;

        unsigned int GetSize() const {
            return count * AttributeTypeSize(type);
        }
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout();
        VertexBufferLayout(std::initializer_list<VertexBufferEntry> initEntries);

        void Push(AttributeType type, unsigned int count, bool normalized = false);

        unsigned int GetStride() const;
        const std::vector<VertexBufferEntry>& GetEntries() const;

    private:
        std::vector<VertexBufferEntry> entries;
        unsigned int stride;
    };

    class VertexBuffer {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void Load(const void* data, unsigned int size);

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int id;
    };
}
