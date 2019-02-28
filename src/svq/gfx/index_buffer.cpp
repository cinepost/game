#include "svq/gfx/index_buffer.h"

#include "svq/gfx/gl_index_buffer.h"


namespace svq {
namespace gfx {

IndexBuffer* IndexBuffer::create(uint16* data, uint count) {
	#ifdef _SVQ_OPENGL
	return new GLIndexBuffer(data, count);
	#endif
	
	return nullptr;
}

IndexBuffer* IndexBuffer::create(uint* data, uint count) {
	#ifdef _SVQ_OPENGL
	return new GLIndexBuffer(data, count);
	#endif

	return nullptr;
}
	
}
}