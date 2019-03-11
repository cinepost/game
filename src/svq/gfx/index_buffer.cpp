#include <iostream>

#include "svq/gfx/index_buffer.h"
#include "svq/gfx/ogl/gl_index_buffer.h"


namespace svq {
namespace gfx {

IndexBuffer* IndexBuffer::create(uint16* data, uint count) {
	std::cout << "GL_IndexBuffer creation\n";
	#ifdef _SVQ_OPENGL
	return new GL_IndexBuffer(data, count);
	#else 
	return nullptr;
	#endif
}

IndexBuffer* IndexBuffer::create(uint* data, uint count) {
	std::cout << "GL_IndexBuffer creation\n";
	#ifdef _SVQ_OPENGL
	return new GL_IndexBuffer(data, count);
	#else
	return nullptr;
	#endif
}
	
}
}