#ifndef RENDERER__H
#define RENDERER__H

#include "svq/api.h"
#include "svq/math/vec2.h"
#include "svq/gfx/shader.h"
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

struct UniformBuffer {
	byte* buffer;
	uint size;

	UniformBuffer() {}
	UniformBuffer(byte* buffer, uint size) : buffer(buffer), size(size) {
		memset(buffer, 0, size);
	}
};

struct BR2DSystemUniform {
	UniformBuffer buffer;
	uint offset;

	BR2DSystemUniform() {}
	BR2DSystemUniform(const UniformBuffer& buffer, uint offset) : buffer(buffer), offset(offset) {
	}
};

class Renderer_2D { 
    public:
    	Renderer_2D(uint width, uint height);
    	Renderer_2D(const math::Vec2<uint>& screenSize);
    	~Renderer_2D();

    	void start();
    	void stop();
    	void push(const Renderable_2D* renderable);
    	void flush();

    private:
    	void _init();

    private:
    	std::vector<BR2DSystemUniform> m_SystemUniforms;
			std::vector<UniformBuffer> m_SystemUniformBuffers;

			Shader* m_Shader;
    	RenderTarget m_Target;
    	VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			VertexData* m_Buffer;
			FrameBuffer* m_Framebuffer;
			FrameBuffer* m_PostEffectsBuffer;

			//std::map<uint sort_key, Renderable_2D* renderable> m_Renderables; 

			VertexArray* m_ScreenQuad;

			bool m_PostEffectsEnabled;

			uint m_IndexCount;
			math::Vec2<uint> m_ScreenSize, m_ViewportSize;
};
    
}
}

#endif // RENDERER__H