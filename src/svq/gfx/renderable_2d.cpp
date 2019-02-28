#include "svq/gfx/renderable_2d.h"
#include "svq/gfx/renderer_2d.h"

namespace svq {
namespace gfx {


Renderable_2D::Renderable_2D() : m_Texture(nullptr) {
	m_UVs = getDefaultUVs();
}

Renderable_2D::Renderable_2D(math::Vec3f pos, math::Vec2f size, math::Vec4f color)
	: m_Bounds(pos, size), m_Color(color), m_Texture(nullptr), m_Visible(true) {
	m_UVs = getDefaultUVs();
}

Renderable_2D::~Renderable_2D() { }

void Renderable_2D::submit(Renderer_2D* renderer) const {
	renderer->push(this);
}


void Renderable_2D::setColor(const math::Vec4f& color) {
	m_Color =color;
}

const std::vector<math::Vec2f>& Renderable_2D::getDefaultUVs() {
	static std::vector<math::Vec2f> results;
	if (!results.size())
	{
		results.push_back(math::Vec2f(0, 1));
		results.push_back(math::Vec2f(1, 1));
		results.push_back(math::Vec2f(1, 0));
		results.push_back(math::Vec2f(0, 0));
	}
	return results;
}

}
}