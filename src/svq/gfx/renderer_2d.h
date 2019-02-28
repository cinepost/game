#ifndef RENDERER__H
#define RENDERER__H

#include "svq/api.h"
#include "svq/gfx/vertex_array.h"
#include "svq/gfx/index_buffer.h"
#include "svq/gfx/renderable_2d.h"

namespace svq { 
namespace gfx {

enum class SVQ_API RenderTarget {
		SCREEN = 0,
		BUFFER = 1
};

class Renderer_2D { 
    public:
    	static Renderer_2D* create();

    	void push(const Renderable_2D* renderable);
    	void flush();

    private:
    	RenderTarget m_Target;
    	VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			VertexData* m_Buffer;

			uint m_IndexCount;
};
    
}
}

#endif // RENDERER__H