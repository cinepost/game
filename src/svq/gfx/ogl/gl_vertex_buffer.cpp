#include "svq/gfx/ogl/gl_vertex_buffer.h"

namespace svq {
namespace gfx {
	
	static uint SPBufferUsageToOpenGL(BufferType type)
	{
		switch (type)
		{
			case BufferType::STATIC: return GL_STATIC_DRAW;
			case BufferType::DYNAMIC: return GL_DYNAMIC_DRAW;
		}
		return 0;
	}

	GL_VertexBuffer::GL_VertexBuffer(BufferType type)
		: m_Usage(type) {
		glGenBuffers(1, &m_Handle);
	}

	GL_VertexBuffer::~GL_VertexBuffer() {
		glDeleteBuffers(1, &m_Handle);
	}

	void GL_VertexBuffer::resize(uint size) {
		m_Size = size;

		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		glBufferData(GL_ARRAY_BUFFER, size, NULL, SPBufferUsageToOpenGL(m_Usage));
	}

	void GL_VertexBuffer::setLayout(const BufferLayout& bufferLayout) {
		m_Layout = bufferLayout;
		const std::vector<BufferElement>& layout = bufferLayout.getLayout();
		for (uint i = 0; i < layout.size(); i++) {
			const BufferElement& element = layout[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, bufferLayout.getStride(), (const void*)element.offset);
		}
	}

	void GL_VertexBuffer::setData(uint size, const void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		glBufferData(GL_ARRAY_BUFFER, size, data, SPBufferUsageToOpenGL(m_Usage));
	}

	void* GL_VertexBuffer::getPointerInternal() {
		void* result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		return result;
	}

	void GL_VertexBuffer::releasePointer() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void GL_VertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		setLayout(m_Layout);
	}

	void GL_VertexBuffer::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
}