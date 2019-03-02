#include "svq/gfx/vertex_array.h"

#include "svq/gfx/ogl/gl_vertex_array.h"
//#include "svq/gfx/d3d/dx_vertex_array.h"


namespace svq{ namespace gfx{

VertexArray* VertexArray::create() {
	#ifdef _SVQ_OPENGL
	return new GL_VertexArray();
	#else
	//return new DX_VertexArray();
	#endif
}

}}