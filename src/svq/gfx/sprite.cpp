#include "svq/gfx/sprite.h"

namespace svq {
namespace gfx {

	Sprite::Sprite() : Renderable_2D() {
	}

	//Sprite::Sprite(API::Texture2D* texture)
	//	: Renderable2D(maths::vec3(0.0f, 0.0f, 0.0f), maths::vec2((float)texture->GetWidth(), (float)texture->GetHeight()), 0xffffffff) {
	//	m_Texture = texture;
	//}

	//Sprite::Sprite(float x, float y, API::Texture2D* texture)
	//	: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2((float)texture->GetWidth(), (float)texture->GetHeight()), 0xffffffff) {
	//	m_Texture = texture;
	//}

	Sprite::Sprite(float x, float y, float width, float height, const math::Vec4f& color)
		: Renderable_2D(math::Vec3f(x, y, 0.0f), math::Vec2f(width, height), color) { }

	//Sprite::Sprite(float x, float y, float width, float height, API::Texture* texture)
	//	: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), 0xffffffff) {
	//	m_Texture = texture;
	//}

	void Sprite::setUV(const std::vector<math::Vec2f>& uv) { m_UVs = uv; }

} }