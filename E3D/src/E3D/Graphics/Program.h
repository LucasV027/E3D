#pragma once

#include <filesystem>
#include <unordered_map>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "E3D/Core/Base.h"

namespace E3D {
    namespace fs = std::filesystem;

    enum class ShaderType {
        Fragment = GL_FRAGMENT_SHADER,
        Vertex = GL_VERTEX_SHADER,
    };

    class Program : RefOnly<Program> {
    public:
        explicit Program(InternalTag);
        ~Program();

        static Ref<Program> Create(const fs::path& vsPath, const fs::path& fsPath);

        void Bind() const;
        void Unbind() const;

        template <typename T>
        void SetUniform(const std::string& name, const T& value) {
            int location = GetUniformLocation(name);

            // clang-format off
            if constexpr (std::is_same_v<T, float>) { glUniform1f(location, value); }
            else if constexpr (std::is_same_v<T, int>) { glUniform1i(location, value); }
            else if constexpr (std::is_same_v<T, unsigned int>) { glUniform1ui(location, value); }
            else if constexpr (std::is_same_v<T, glm::vec2>) { glUniform2fv(location, 1, &value[0]); }
            else if constexpr (std::is_same_v<T, glm::vec3>) { glUniform3fv(location, 1, &value[0]); }
            else if constexpr (std::is_same_v<T, glm::vec4>) { glUniform4fv(location, 1, &value[0]); }
            else if constexpr (std::is_same_v<T, glm::mat4>) { glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]); }
            else { static_assert([] { return false; }(), "Unsupported uniform type"); }
            // clang-format on
        }

    private:
        void Init();
        bool Attach(ShaderType type, const fs::path& filepath) const;
        bool Link() const;

    private:
        int GetUniformLocation(const std::string& name) const;
        static bool CompileShader(unsigned int shader, const std::string& source);
        static std::string ReadFile(const fs::path& filepath);

    private:
        unsigned int id;
        mutable std::unordered_map<std::string, GLint> uniformCache;
    };
}

