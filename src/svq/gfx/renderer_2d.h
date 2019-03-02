#ifndef RENDERER__H
#define RENDERER__H

#include "svq/api.h"
#include "svq/math/vec2.h"
#include "svq/gfx/frame_buffer.h"
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
    	Renderer_2D(uint width, uint height);
    	Renderer_2D(const math::Vec2<uint>& screenSize);
    	~Renderer_2D();

    	void push(const Renderable_2D* renderable);
    	void flush();

    private:
    	void init();

    private:
    	RenderTarget m_Target;
    	VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			VertexData* m_Buffer;
			FrameBuffer* m_Framebuffer;

			uint m_IndexCount;
			math::Vec2<uint> m_ScreenSize, m_ViewportSize;
};
    
}
}

#endif // RENDERER__H