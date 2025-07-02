#pragma once
#include <filesystem>

namespace E3D {
    class Texture {
    public:
        enum class Type { Texture2D };

        enum class WrapMode { Clamp, Repeat, ClampEdge, ClampBorder };

        enum class FilterMode { Nearest, Linear };

        enum class Format { R8, RGB8, RGBA8, RGBA32F };

        struct Specification {
            int width = 1;
            int height = 1;

            Type type = Type::Texture2D;
            Format format = Format::RGBA8;
            WrapMode wrapModeT = WrapMode::Clamp;
            WrapMode wrapModeS = WrapMode::Clamp;
            FilterMode minFilter = FilterMode::Nearest;
            FilterMode magFilter = FilterMode::Linear;

            bool generateMipMaps = false;
            FilterMode minMipMapFilter = FilterMode::Linear;
        };

    public:
        explicit Texture(const Specification& spec);
        ~Texture();

        void LoadFromFile(const std::filesystem::path& path) const;
        void Submit(const void* data, unsigned int size) const;

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

    private:
        unsigned int id;
        Specification spec;
    };
}

