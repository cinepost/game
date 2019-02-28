#include "svq/gfx/vertex_buffer.h"

#include "svq/gfx/ogl/gl_vertex_buffer.h"
#include "svq/gfx/d3d/dx_Vertex_buffer.h"


namespace svq {
namespace graphics {

VertexBuffer* VertexBuffer::create(BufferType type) {
	#ifdef _SVQ_OPENGL
	return new GLVertexBuffer(type);
	#endif

	return nullptr;
}

}
}