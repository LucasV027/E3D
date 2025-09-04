#include "VertexBufferLayout.h"

namespace E3D {
    VertexBufferLayout::VertexBufferLayout(const std::initializer_list<LayoutEntry>& list) {
        unsigned int offset = 0;
        for (auto entry : list) {
            entry.offset = offset;
            offset += entry.count * AttributeTypeSize(entry.type);
            entries.push_back(entry);
        }
        stride = offset;
    }

    const std::vector<LayoutEntry>& VertexBufferLayout::GetEntries() const { return entries; }
    unsigned int VertexBufferLayout::GetStride() const { return stride; }

    unsigned int VertexBufferLayout::AttributeTypeSize(const AttributeType type) {
        switch (type) {
        case AttributeType::Byte:
        case AttributeType::UnsignedByte: return 1;
        case AttributeType::Short:
        case AttributeType::UnsignedShort: return 2;
        case AttributeType::Int:
        case AttributeType::UnsignedInt:
        case AttributeType::Float: return 4;
        case AttributeType::Double: return 8;
        }
        return 0;
    }
}
