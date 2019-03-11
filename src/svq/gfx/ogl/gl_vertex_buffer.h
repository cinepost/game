#ifndef GL_VERTEX_BUFFER__H
#define GL_VERTEX_BUFFER__H

#include "svq/gfx/vertex_buffer.h"

namespace svq {
namespace gfx {

class GL_VertexBuffer : public VertexBuffer {
	public:
		GL_VertexBuffer(BufferType usage);
		~GL_VertexBuffer();

		void resize(uint size) override;
		void setLayout(const BufferLayout& layout) override;
		void setData(uint size, const void* data) override;

		void releasePointer() override;

		void bind() override;
		void unbind() override;

	protected:
		void* getPointerInternal() override;
		static uint bufferUsageToOpenGL(BufferType type);

	private:
		uint m_Handle;
		BufferType m_Usage;
		uint m_Size;
		BufferLayout m_Layout;
};


}
}

#endif // GL_VERTEX_BUFFER__H