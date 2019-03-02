#ifndef APP__H
#define APP__H

#define GL_GLEXT_PROTOTYPES

#include <vector>
#include <iostream>

#include <SDL.h>
#include <SDL_opengl.h>

#include "svq/api.h"
#include "svq/gfx/sprite.h"
#include "svq/gfx/renderer_2d.h"

namespace svq{
	
class SVQ_API App {
	public:
		App(bool retrocore = false);
		~App();
		bool init();

		int run();
		void onRender();

	private:
		SDL_Window *m_Window;
    SDL_GLContext m_Context;

		bool m_Retrocore;
		bool isFullscreen;

		// test stuff
		gfx::Renderer_2D *m_Renderer;
		gfx::Sprite *m_Sprite;
};

}

#endif // APP__H