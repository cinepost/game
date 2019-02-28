#include "svq/gfx/renderer_2d.h"

namespace svq {
namespace gfx {

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

}
}