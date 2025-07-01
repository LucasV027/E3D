#pragma once

namespace E3D {
    enum class TextureType { Texture2D };

    enum class WrapMode { Clamp, Repeat, ClampEdge, ClampBorder };

    enum class FilterMode { Nearest, Linear };

    enum class TextureFormat { R8, RGB8, RGBA8, RGBA32F };

    struct TextureSpecification {
        int width = 1;
        int height = 1;

        TextureType type = TextureType::Texture2D;
        TextureFormat format = TextureFormat::RGBA8;
        WrapMode wrapModeT = WrapMode::Clamp;
        WrapMode wrapModeS = WrapMode::Clamp;
        FilterMode minFilter = FilterMode::Nearest;
        FilterMode magFilter = FilterMode::Linear;

        bool generateMipMaps = false;
        FilterMode minMipMapFilter = FilterMode::Linear;
    };

    class Texture {
    public:
        explicit Texture(const TextureSpecification& spec);
        ~Texture();

        void Submit(const void* data, unsigned int size) const;

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

    private:
        unsigned int id;
        TextureSpecification spec;
    };
}

