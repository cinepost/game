#ifndef INDEX_BUFFER__H
#define INDEX_BUFFER__H

#include "svq/gfx/vertex_buffer.h"

namespace svq { 
namespace gfx {

class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};
		static IndexBuffer* create(uint16* data, uint count);
		static IndexBuffer* create(uint* data, uint count);

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual uint getCount() const = 0;
};

}
}

#endif // INDEX_BUFFER__H