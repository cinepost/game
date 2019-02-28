#ifndef VERTEX_ARRAY__H
#define VERTEX_ARRAY__H

#include <vector>

#include "svq/gfx/vertex_buffer.h"

namespace svq {
namespace gfx {

class VertexArray {
	public:
		static VertexArray* create();

		virtual VertexBuffer* getBuffer(uint index = 0) = 0;
		virtual void pushBuffer(VertexBuffer* buffer) = 0;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void draw(uint count) const = 0;

	private:
		uint m_ID;
		std::vector<VertexBuffer*> m_Buffers;

	};

}
}

#endif // VERTEX_ARRAY__H 