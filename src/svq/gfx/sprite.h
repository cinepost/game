#ifndef SPRITE__H
#define SPRITE__H

#include "svq/api.h"
#include "svq/math/vec2.h"
#include "svq/math/vec4.h"
#include "svq/gfx/renderable_2d.h"

namespace svq {
namespace gfx {

class SVQ_API Sprite : public Renderable_2D {
	public:
		//Sprite(API::Texture2D* texture);
		//Sprite(float x, float y, API::Texture2D* texture);
		Sprite(float x, float y, float width, float height, const math::Vec4f& color);
		//Sprite(float x, float y, float width, float height, API::Texture* texture);

		void setUV(const std::vector<math::Vec2f>& uv);

		//inline void setTexture(API::Texture2D* texture) { m_Texture = texture; }

	protected:
		Sprite();

};

}
}

#endif // SPRITE__H