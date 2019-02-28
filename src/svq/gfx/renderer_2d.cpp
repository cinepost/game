#include "svq/gfx/renderer_2d.h"

namespace svq {
namespace gfx {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32 - 1


Renderer_2D::Renderer_2D(uint width, uint height)
		: m_IndexCount(0), m_ScreenSize(math::Vec2<uint>(width, height)), m_ViewportSize(math::Vec2<uint>(width, height)) {
	init();
}


Renderer_2D::Renderer_2D(const math::Vec2<uint>& screenSize)
		: m_IndexCount(0), m_ScreenSize(screenSize), m_ViewportSize(screenSize) {
	init();
}


void Renderer_2D::init() {
	VertexBuffer* buffer = VertexBuffer::create(BufferType::DYNAMIC);
	buffer->resize(RENDERER_BUFFER_SIZE);

	BufferLayout layout;
	layout.push<math::Vec3f>("POSITION"); // Position
	layout.push<math::Vec2f>("TEXCOORD"); // UV
	layout.push<float>("ID"); // Texture Index
	layout.push<float>("COLOR", 4, true); // Color
	buffer->setLayout(layout);

	m_VertexArray = VertexArray::create();
	m_VertexArray->pushBuffer(buffer);

	uint* indices = spnew uint[RENDERER_INDICES_SIZE];

	int32 offset = 0;

	for (int32 i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
		indices[i] = offset + 0; indices[i + 1] = offset + 1; indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2; indices[i + 4] = offset + 3; indices[i + 5] = offset + 0;
		offset += 4;
	}

	m_IndexBuffer = IndexBuffer::create(indices, RENDERER_INDICES_SIZE);
	m_VertexArray->unbind();

	// Setup Framebuffer
	m_Framebuffer = Framebuffer2D::create(m_ViewportSize.x, m_ViewportSize.y);

	//m_FramebufferMaterial = new Material(ShaderFactory::SimpleShader());
	//m_FramebufferMaterial->SetUniform("pr_matrix", maths::mat4::Orthographic(0, (float)m_ScreenSize.x, (float)m_ScreenSize.y, 0, -1.0f, 1.0f));
	//m_FramebufferMaterial->SetTexture("u_Texture", m_Framebuffer->GetTexture());
	//m_ScreenQuad = MeshFactory::CreateQuad(0, 0, (float)m_ScreenSize.x, (float)m_ScreenSize.y);

	//m_PostEffects = spnew PostEffects();
	//m_PostEffectsBuffer = Framebuffer2D::Create(m_ViewportSize.x, m_ViewportSize.y);
}


void Renderer_2D::push(const Renderable_2D* renderable){
	if (!renderable->isVisible())
		return;

	//const math::Bbox2f& bounds = renderable->getBounds();
	//const math::Vec3f min = bounds.getMinimumBound();
	//const math::Vec3f max = bounds.getMaximumBound();

	const math::Vec4f color = renderable->getColor();
	const std::vector<math::Vec2f>& uv = renderable->getUVs();
	const Texture* texture = renderable->getTexture();

	float textureSlot = 0.0f;
	//if (texture)
	//	textureSlot = submitTexture(renderable->getTexture());

	//mat4 maskTransform = mat4::Identity();
	//float mid = m_Mask ? SubmitTexture(m_Mask->texture) : 0.0f;
	//float ms = 0.0f;

	//if (s_MaskEnabled && m_Mask != nullptr)
	//{
	//	maskTransform = mat4::Invert(m_Mask->transform);
	//	ms = SubmitTexture(m_Mask->texture);
	//}

	//math::Vec3f vertex = *m_TransformationBack * min;
	//m_Buffer->vertex = vertex;
	m_Buffer->uv = uv[0];
	//m_Buffer->mask_uv = maskTransform * vertex;
	m_Buffer->texture_id = textureSlot;
	//m_Buffer->mid = ms;
	m_Buffer->color = color;
	m_Buffer++;

	//vertex = *m_TransformationBack * vec3(max.x, min.y);
	//m_Buffer->vertex = vertex;
	m_Buffer->uv = uv[1];
	//m_Buffer->mask_uv = maskTransform * vertex;
	m_Buffer->texture_id = textureSlot;
	//m_Buffer->mid = ms;
	m_Buffer->color = color;
	m_Buffer++;

	//vertex = *m_TransformationBack * max;
	//m_Buffer->vertex = vertex;
	m_Buffer->uv = uv[2];
	//m_Buffer->mask_uv = maskTransform * vertex;
	m_Buffer->texture_id = textureSlot;
	//m_Buffer->mid = ms;
	m_Buffer->color = color;
	m_Buffer++;

	//vertex = *m_TransformationBack * vec3(min.x, max.y);
	//m_Buffer->vertex = vertex;
	m_Buffer->uv = uv[3];
	//m_Buffer->mask_uv = maskTransform * vertex;
	m_Buffer->texture_id = textureSlot;
 	//m_Buffer->mid = ms;
	m_Buffer->color = color;
	m_Buffer++;

	m_IndexCount += 6;
}

Renderer_2D::~Renderer_2D() {
	delete m_IndexBuffer;
	delete m_VertexArray;
	//delete m_ScreenQuad;
}

}
}