#include "VertexArray.h"

#include "glad/glad.h"

namespace E3D {
    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &handle);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(handle);
    }

    void VertexArray::Unbind() const {
        glBindVertexArray(0);
    }
}
