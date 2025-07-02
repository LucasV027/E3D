#include "Texture.h"

#include <stdexcept>

#include "glad/glad.h"
#include "stb_image.h"

namespace E3D {
    namespace Helper {
        static unsigned int TextureTypeToGL(const Texture::Type type) {
            switch (type) {
            case Texture::Type::Texture2D: return GL_TEXTURE_2D;
            default:
                throw std::invalid_argument("Unknown TextureType");
            }
        }

        static unsigned int FormatToGL(const Texture::Format format) {
            switch (format) {
            case Texture::Format::R8: return GL_RED;
            case Texture::Format::RGB8: return GL_RGB;
            case Texture::Format::RGBA8:
            case Texture::Format::RGBA32F: return GL_RGBA;
            default:
                throw std::invalid_argument("Unknown Format");
            }
        }

        static unsigned int FormatToGLInternal(const Texture::Format format) {
            switch (format) {
            case Texture::Format::R8: return GL_R8;
            case Texture::Format::RGB8: return GL_RGB8;
            case Texture::Format::RGBA8: return GL_RGBA8;
            case Texture::Format::RGBA32F: return GL_RGBA32F;
            default:
                throw std::invalid_argument("Unknown Format");
            }
        }

        static int WrapModeToGL(const Texture::WrapMode mode) {
            switch (mode) {
            case Texture::WrapMode::Clamp: return GL_CLAMP;
            case Texture::WrapMode::Repeat: return GL_REPEAT;
            case Texture::WrapMode::ClampEdge: return GL_CLAMP_TO_EDGE;
            case Texture::WrapMode::ClampBorder: return GL_CLAMP_TO_BORDER;
            default:
                throw std::invalid_argument("Unknown WrapMode");
            }
        }

        static int FilterModeToGL(const Texture::FilterMode mode) {
            switch (mode) {
            case Texture::FilterMode::Nearest: return GL_NEAREST;
            case Texture::FilterMode::Linear: return GL_LINEAR;
            default:
                throw std::invalid_argument("Unknown FilterMode");
            }
        }

        static unsigned int FormatToBPP(const Texture::Format format) {
            switch (format) {
            case Texture::Format::R8: return 1;
            case Texture::Format::RGB8: return 3;
            case Texture::Format::RGBA8: return 4;
            case Texture::Format::RGBA32F: return 16;
            default:
                throw std::invalid_argument("Unknown Format");
            }
        }

        static int CombineFilterModes(const Texture::FilterMode base, const Texture::FilterMode mipmap) {
            if (mipmap == Texture::FilterMode::Nearest) {
                return (base == Texture::FilterMode::Nearest) ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_NEAREST;
            }
            // mipmap == Linear
            return (base == Texture::FilterMode::Nearest) ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    Texture::Texture(const Specification& spec) : id(0), spec(spec) {
        glCreateTextures(Helper::TextureTypeToGL(spec.type), 1, &id);
        glTextureStorage2D(id, 1, Helper::FormatToGLInternal(spec.format), spec.width, spec.height);

        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, Helper::FilterModeToGL(spec.minFilter));
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, Helper::FilterModeToGL(spec.magFilter));

        glTextureParameteri(id, GL_TEXTURE_WRAP_S, Helper::WrapModeToGL(spec.wrapModeS));
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, Helper::WrapModeToGL(spec.wrapModeT));
    }

    void Texture::Submit(const void* data, const unsigned int size) const {
        const unsigned int expected = spec.width * spec.height * Helper::FormatToBPP(spec.format);
        if (size != expected) {
            throw std::invalid_argument("Invalid size for texture data");
        }

        const unsigned int dataType = (spec.format == Format::RGBA32F) ? GL_FLOAT : GL_UNSIGNED_BYTE;
        glTextureSubImage2D(id, 0, 0, 0, spec.width, spec.height, Helper::FormatToGL(spec.format), dataType,
                            data);

        if (spec.generateMipMaps) {
            glGenerateMipmap(id);
            glTextureParameteri(id, GL_TEXTURE_MIN_FILTER,
                                Helper::CombineFilterModes(spec.minFilter, spec.minMipMapFilter));
        }
    }

    Texture::~Texture() {
        glDeleteTextures(1, &id);
    }

    void Texture::LoadFromFile(const std::filesystem::path& path) const {
        int width, height, bpp;
        int desiredBPP = Helper::FormatToBPP(spec.format);

        auto* buffer = stbi_load(path.string().c_str(), &width, &height, &bpp, desiredBPP);

        if (!buffer) {
            throw std::runtime_error("Failed to load " + path.string() + " texture");
        }

        Submit(buffer, width * height * desiredBPP);
        stbi_image_free(buffer);
    }

    void Texture::Bind(const unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(Helper::TextureTypeToGL(spec.type), id);
    }

    void Texture::Unbind() const {
        glBindTexture(Helper::TextureTypeToGL(spec.type), 0);
    }
}
