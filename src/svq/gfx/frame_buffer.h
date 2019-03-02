#ifndef FRAME_BUFFER__H
#define FRAME_BUFFER__H

#include "svq/api.h"
#include "svq/types.h"
#include "svq/math/vec4.h"
#include "svq/gfx/texture.h"
//#include "svq/Framebuffer.h"

namespace svq{ namespace gfx{

class SVQ_API FrameBuffer  {
	public:
		static FrameBuffer* create(uint width, uint height);
		
		virtual void setClearColor(const math::Vec4f& color) = 0;		

		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
		virtual Texture* getTexture() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void clear() = 0;

	private:
		virtual void init() {};
};

}}

#endif // FRAME_BUFFER__H