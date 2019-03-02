#ifndef GL_VERTEX_ARRAY__H
#define GL_VERTEX_ARRAY__H

#include <vector>

#include "svq/gfx/vertex_buffer.h"
#include "svq/gfx/vertex_array.h"

namespace svq{ namespace gfx{

class GL_VertexArray : public VertexArray {
	public:
		GL_VertexArray();
		~GL_VertexArray();

		inline VertexBuffer* getBuffer(uint index = 0) override { return m_Buffers[index]; }
		void pushBuffer(VertexBuffer* buffer) override;

		void bind() const override;
		void unbind() const override;

		void draw(uint count) const override;

	private:
		uint m_Handle;
		std::vector<VertexBuffer*> m_Buffers;
};

}}

#endif // GL_VERTEX_ARRAY__H