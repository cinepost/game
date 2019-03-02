#ifndef GL_FRAME_BUFFER__H
#define GL_FRAME_BUFFER__H

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#include "svq/gfx/texture.h"
#include "svq/gfx/frame_buffer.h"
#include "svq/gfx/ogl/gl_texture.h"
//#include "GLCommon.h"

namespace svq{ namespace gfx{

class GL_FrameBuffer : public FrameBuffer {
	public:
		GL_FrameBuffer(uint width, uint height);
		~GL_FrameBuffer();

		void bind() const override;
		void unbind() const override;
		void clear() override;

		inline uint getWidth() const override { return m_Width; }
		inline uint getHeight() const override { return m_Height; }

		inline Texture* getTexture() const override { return m_Texture; }
		inline void setClearColor(const math::Vec4f& color) override { m_ClearColor = color; }

	private:
		void init() override;

	private:
		uint m_FramebufferHandle;
		uint m_DepthbufferHandle;

		uint m_Width, m_Height;
		math::Vec4f m_ClearColor;
		GL_Texture* m_Texture;

};

}}

#endif // GL_FRAME_BUFFER__H