#pragma once

#include <vector>

#include "glad/glad.h"

namespace E3D {
    enum class AttributeType : GLenum {
        Byte = GL_BYTE,
        UnsignedByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        UnsignedInt = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
        Double = GL_DOUBLE
    };

    struct LayoutEntry {
        AttributeType type;
        unsigned int count;
        bool normalized;
        unsigned int offset = 0;
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout() = default;
        VertexBufferLayout(const std::initializer_list<LayoutEntry>& list);

        const std::vector<LayoutEntry>& GetEntries() const;
        unsigned int GetStride() const;

    private:
        static unsigned int AttributeTypeSize(AttributeType type);

    private:
        std::vector<LayoutEntry> entries;
        unsigned int stride = 0;
    };
}
