#include "svq/gfx/frame_buffer.h"


#include "svq/gfx/ogl/gl_frame_buffer.h"
//#include "svq/gfx/d3d/dx_frame_buffer.h"

#include "svq/system/Memory.h"

namespace svq {
namespace gfx {

Framebuffer* Framebuffer::create(uint width, uint height) {
	#ifdef _SVQ_OPENGL
	return new GL_Framebuffer(width, height);
	#endif

	return nullptr;
}

}
}