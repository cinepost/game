#include "svq/gfx/ogl/gl_vertex_array.h"

namespace svq{ namespace gfx{

GL_VertexArray::GL_VertexArray() {}

GL_VertexArray::~GL_VertexArray() {}

void GL_VertexArray::pushBuffer(VertexBuffer* buffer){
	m_Buffers.push_back(buffer);
}

void GL_VertexArray::bind() const{
	m_Buffers.front()->bind();
}

void GL_VertexArray::unbind() const{
	m_Buffers.front()->unbind();
}

void GL_VertexArray::draw(uint count) const {
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}

} }