#include "svq/gfx/ogl/gl_common.h"
#include "svq/gfx/ogl/gl_index_buffer.h"

namespace svq { 
namespace gfx {

GL_IndexBuffer::GL_IndexBuffer(uint16* data, uint count) : m_Count(count) {
	GL_CALL(glGenBuffers(1, &m_Handle));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW));
}

GL_IndexBuffer::GL_IndexBuffer(uint* data, uint count) : m_Count(count) {
	GL_CALL(glGenBuffers(1, &m_Handle));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
}

GL_IndexBuffer::~GL_IndexBuffer() {
	GL_CALL(glDeleteBuffers(1, &m_Handle));
}

void GL_IndexBuffer::bind() const {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
}

void GL_IndexBuffer::unbind() const {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

uint GL_IndexBuffer::getCount() const {
	return m_Count;
}

}
}