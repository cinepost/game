#ifndef GL_INDEX_BUFFER__H
#define GL_INDEX_BUFFER__H

#include "svq/gfx/index_buffer.h"

namespace svq {
namespace gfx {

class GL_IndexBuffer : public IndexBuffer {
	public:
		GL_IndexBuffer(uint16* data, uint count);
		GL_IndexBuffer(uint* data, uint count);
		~GL_IndexBuffer();

		void bind() const;
		void unbind() const;
		uint getCount() const;

	private:
		GLuint m_Handle;
		uint m_Count;
};


}
}

#endif // GL_INDEX_BUFFER__H