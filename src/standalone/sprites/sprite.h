#ifndef SPRITE__H
#define SPRITE__H

#include <string>

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

namespace Sprites {

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

}


#endif // SPRITE__H