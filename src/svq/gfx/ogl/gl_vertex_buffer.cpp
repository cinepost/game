#include <iostream>

#include "svq/gfx/ogl/gl_common.h"
#include "svq/gfx/ogl/gl_vertex_buffer.h"

namespace svq{ namespace gfx{
	
	uint GL_VertexBuffer::bufferUsageToOpenGL(BufferType type) {
		switch (type) {
			case BufferType::STATIC: return GL_STATIC_DRAW;
			case BufferType::DYNAMIC: return GL_DYNAMIC_DRAW;
		}
		return 0;
	}

	GL_VertexBuffer::GL_VertexBuffer(BufferType type) : m_Usage(type) {
		GL_CALL(glGenBuffers(1, &m_Handle));
	}

	GL_VertexBuffer::~GL_VertexBuffer() {
		GL_CALL(glDeleteBuffers(1, &m_Handle));
	}

	void GL_VertexBuffer::resize(uint size) {
		m_Size = size;

		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, NULL, bufferUsageToOpenGL(m_Usage)));
	}

	void GL_VertexBuffer::setLayout(const BufferLayout& bufferLayout) {
		m_Layout = bufferLayout; // keep layout for later usage
		const std::vector<BufferElement>& layout = m_Layout.getElements(); // actual layout elements list
		for (uint i = 0; i < layout.size(); i++) {
			const BufferElement& element = layout[i];
			GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, m_Layout.getStride(), (GLvoid *)element.offset));
			GL_CALL(glEnableVertexAttribArray(i));
		}
	}

	void GL_VertexBuffer::setData(uint size, const void* data) {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, bufferUsageToOpenGL(m_Usage)));
	}

	void* GL_VertexBuffer::getPointerInternal() {
		GL_CALL(void* result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		return result;
	}

	void GL_VertexBuffer::releasePointer() {
		GL_CALL(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

	void GL_VertexBuffer::bind() {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		setLayout(m_Layout);
	}

	void GL_VertexBuffer::unbind() {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}}