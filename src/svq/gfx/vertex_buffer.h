#ifndef VERTEX_BUFFER__H
#define VERTEX_BUFFER__H

#include "svq/gfx/buffer_layout.h"

namespace svq {
namespace gfx {

enum class BufferType {
	STATIC, DYNAMIC
};

class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};
		static VertexBuffer* create(BufferType type = BufferType::STATIC);

		virtual void resize(uint size) = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual void setData(uint size, const void* data) = 0;

		virtual void releasePointer() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		template<typename T>
		T* getPointer(){
			return (T*)getPointerInternal();
		}
	
	protected:
		virtual void* getPointerInternal() = 0;

};

}
}

#endif // VERTEX_BUFFER__H 