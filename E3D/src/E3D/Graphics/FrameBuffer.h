#pragma once

#include <unordered_map>

#include "Texture.h"
#include "RenderBuffer.h"
#include "E3D/Core/Base.h"

namespace E3D {
    class FrameBuffer : public RefOnly<FrameBuffer> {
    public:
        enum class Attachment {
            Color0,
            Color1,
            Color2,
            Color3,
            Depth,
            Stencil,
            DepthStencil
        };

        explicit FrameBuffer(InternalTag) {}
        ~FrameBuffer();
        void Bind() const;
        void Unbind();

        class Builder {
        public:
            Builder();
            Builder& WithSize(int width, int height);
            Builder& WithTextureAttachment(Attachment attachment, const Ref<Texture>& texture);
            Builder& WithRenderBufferAttachment(Attachment attachment, const Ref<RenderBuffer>& renderBuffer);
            Ref<FrameBuffer> Build();

        private:
            Ref<FrameBuffer> fbo;
        };

    private:
        unsigned int id = 0;
        int width = -1;
        int height = -1;
        std::unordered_map<Attachment, Ref<Texture>> textureAttachments;
        std::unordered_map<Attachment, Ref<RenderBuffer>> renderBufferAttachments;
    };
}
