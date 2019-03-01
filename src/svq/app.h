#ifndef APP__H
#define APP__H

#define GL_GLEXT_PROTOTYPES

#include <vector>
#include <iostream>

#include <SDL.h>
#include <SDL_opengl.h>

#include "svq/api.h"

namespace svq{
	
class SVQ_API App {
	public:
		App(bool retrocore = false);
		~App();
		bool init();

		void run();
		int onRender();

	private:
		SDL_Window * m_Window;
    SDL_GLContext m_Context;

		bool m_Retrocore;
		bool isFullscreen = false;
};

}

#endif // APP__H