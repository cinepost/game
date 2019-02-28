#ifndef GL_SPRITE__H
#define GL_SPRITE__H

#include <string>

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "svq/math/vec2.h"

namespace svq { namespace gfx {

struct UVCoord {
	UVCoord():a(0.0f, 0.0f), b(1.0f, 0.0f), c(1.0, 1.0f), d(0.0f, 1.0f) {}
	math::Vec2d a;
	math::Vec2d b;
	math::Vec2d c;
	math::Vec2d d;
};

class Sprite {
	public:
		Sprite();
		~Sprite();

		bool loadFromImage(std::string fileName);
		void render(int x, int y);

	private:
		int mode, width, height;
		GLuint tex_id;
		GLuint vao, vbo;
};

} }


#endif // GL_SPRITE__H