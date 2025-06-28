#include "Program.h"

#include <iostream>
#include <fstream>

#include "glad/glad.h"

namespace E3D {
    Program::Program() : id(0) {}

    Program::~Program() {
        glDeleteProgram(id);
    }

    void Program::Init() { id = glCreateProgram(); }

    bool Program::Attach(ShaderType type, const std::string& filepath) const {
        const auto shaderSource = ReadFile(filepath);
        const auto shader = glCreateShader(static_cast<GLenum>(type));
        if (!CompileShader(shader, shaderSource)) return false;
        glAttachShader(id, shader);
        glDeleteShader(shader);
        return true;
    }

    bool Program::Link() const {
        glLinkProgram(id);
        glValidateProgram(id);

        int success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    void Program::Bind() const {
        glUseProgram(id);
    }

    void Program::Unbind() {
        glUseProgram(0);
    }

    int Program::GetUniformLocation(const std::string& name) const {
        if (uniformCache.contains(name))
            return uniformCache.at(name);

        const int location = glGetUniformLocation(id, name.c_str());
        if (location == -1) {
            std::cerr << "Warning: uniform '" << name << "' doesn't exist or is not used.\n";
        }

        uniformCache[name] = location;
        return location;
    }

    bool Program::CompileShader(const unsigned int shader, const std::string& source) {
        const char* shaderSourcePtr = source.c_str();
        glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLint infoLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
            char infoLog[infoLength];
            glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
            std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    std::string Program::ReadFile(const fs::path& filepath) {
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        if (!file)
            throw std::runtime_error("Failed to open file: " + filepath.string());

        const std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string buffer(size, '\0');
        if (!file.read(buffer.data(), size))
            throw std::runtime_error("Failed to read file: " + filepath.string());

        return buffer;

    }
}
