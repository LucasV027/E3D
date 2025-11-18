#include "VertexArray.h"

#include "glad/gl.h"

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
