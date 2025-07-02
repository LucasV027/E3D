#include "Texture.h"

#include <stdexcept>

#include "glad/glad.h"
#include "stb_image.h"

namespace E3D {
    namespace Helper {
        static unsigned int TextureTypeToGL(const TextureType type) {
            switch (type) {
            case TextureType::Texture2D: return GL_TEXTURE_2D;
            default:
                throw std::invalid_argument("Unknown TextureType");
            }
        }

        static unsigned int TextureFormatToGL(const TextureFormat format) {
            switch (format) {
            case TextureFormat::R8: return GL_RED;
            case TextureFormat::RGB8: return GL_RGB;
            case TextureFormat::RGBA8:
            case TextureFormat::RGBA32F: return GL_RGBA;
            default:
                throw std::invalid_argument("Unknown TextureFormat");
            }
        }

        static unsigned int TextureFormatToGLInternal(const TextureFormat format) {
            switch (format) {
            case TextureFormat::R8: return GL_R8;
            case TextureFormat::RGB8: return GL_RGB8;
            case TextureFormat::RGBA8: return GL_RGBA8;
            case TextureFormat::RGBA32F: return GL_RGBA32F;
            default:
                throw std::invalid_argument("Unknown TextureFormat");
            }
        }

        static int WrapModeToGL(const WrapMode mode) {
            switch (mode) {
            case WrapMode::Clamp: return GL_CLAMP;
            case WrapMode::Repeat: return GL_REPEAT;
            case WrapMode::ClampEdge: return GL_CLAMP_TO_EDGE;
            case WrapMode::ClampBorder: return GL_CLAMP_TO_BORDER;
            default:
                throw std::invalid_argument("Unknown WrapMode");
            }
        }

        static int FilterModeToGL(const FilterMode mode) {
            switch (mode) {
            case FilterMode::Nearest: return GL_NEAREST;
            case FilterMode::Linear: return GL_LINEAR;
            default:
                throw std::invalid_argument("Unknown FilterMode");
            }
        }

        static unsigned int TextureFormatToBPP(const TextureFormat format) {
            switch (format) {
            case TextureFormat::R8: return 1;
            case TextureFormat::RGB8: return 3;
            case TextureFormat::RGBA8: return 4;
            case TextureFormat::RGBA32F: return 16;
            default:
                throw std::invalid_argument("Unknown TextureFormat");
            }
        }

        static int CombineFilterModes(const FilterMode base, const FilterMode mipmap) {
            if (mipmap == FilterMode::Nearest) {
                return (base == FilterMode::Nearest) ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_NEAREST;
            }
            // mipmap == Linear
            return (base == FilterMode::Nearest) ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    Texture::Texture(const TextureSpecification& spec) : id(0), spec(spec) {
        glCreateTextures(Helper::TextureTypeToGL(spec.type), 1, &id);
        glTextureStorage2D(id, 1, Helper::TextureFormatToGLInternal(spec.format), spec.width, spec.height);

        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, Helper::FilterModeToGL(spec.minFilter));
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, Helper::FilterModeToGL(spec.magFilter));

        glTextureParameteri(id, GL_TEXTURE_WRAP_S, Helper::WrapModeToGL(spec.wrapModeS));
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, Helper::WrapModeToGL(spec.wrapModeT));
    }

    void Texture::Submit(const void* data, const unsigned int size) const {
        const unsigned int expected = spec.width * spec.height * Helper::TextureFormatToBPP(spec.format);
        if (size != expected) {
            throw std::invalid_argument("Invalid size for texture data");
        }

        const unsigned int dataType = (spec.format == TextureFormat::RGBA32F) ? GL_FLOAT : GL_UNSIGNED_BYTE;
        glTextureSubImage2D(id, 0, 0, 0, spec.width, spec.height, Helper::TextureFormatToGL(spec.format), dataType,
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
        int desiredBPP = Helper::TextureFormatToBPP(spec.format);

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
