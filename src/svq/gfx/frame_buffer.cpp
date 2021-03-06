#include "svq/gfx/frame_buffer.h"


#include "svq/gfx/ogl/gl_frame_buffer.h"
//#include "svq/gfx/d3d/dx_frame_buffer.h"

//#include "svq/system/Memory.h"

namespace svq{ namespace gfx{

FrameBuffer* FrameBuffer::create(math::Vec2<uint> size) {
	return FrameBuffer::create(size.x, size.y);
}

FrameBuffer* FrameBuffer::create(uint width, uint height) {
	#ifdef _SVQ_OPENGL
	return new GL_FrameBuffer(width, height);
	#endif

	return nullptr;
}

math::Vec2<uint> FrameBuffer::getSize() {
	return math::Vec2<uint>(m_Width, m_Height);
}

}}