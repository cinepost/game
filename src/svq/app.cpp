#include <GL/glew.h>

#include "svq/app.h"
#include "svq/gfx/ogl/gl_common.h"

namespace svq{

	
App::App(bool retrocore) {
	isFullscreen = false;
	m_Retrocore = retrocore;
	m_Renderer = nullptr;
}

App::~App() {
	delete m_Renderer;
	delete m_Sprite;

	if (!m_Retrocore) {
		// SDL cleanup
		SDL_GL_DeleteContext( m_Context );
    SDL_DestroyWindow( m_Window );
    SDL_Quit();
	}
}

bool App::init() {
	static const int width = 480;
  static const int height = 272;

	if (!m_Retrocore) {
		// Standalone SDL version
		if (SDL_Init( SDL_INIT_VIDEO ) != 0) {
			std::cerr << "Error: " << SDL_GetError() << std::endl;
			return false;
  	}

  	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    m_Window = SDL_CreateWindow( "soVoq", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    
    m_Context = SDL_GL_CreateContext( m_Window );
    
    if ( m_Context == NULL ) {
    	std::cerr << "Error: " << SDL_GetError() << std::endl;
    	return false;
    }

  	//Use Vsync
    //if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
    //  printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    //}

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (GLEW_OK != glewError)
    {
        std::cout << "Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
        return EXIT_FAILURE;
    }

    glDisable(GL_CULL_FACE);

    // set viewport
    glViewport( 0, 0, width, height );
	}

	// testing renderer
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	m_Renderer = new gfx::Renderer_2D( width, height);
	m_Sprite = new gfx::Sprite( 10, 10, 32, 32, math::Vec4f(1, 1, 1, 1));

	tst = .0f;

	std::cout << "app init ok" << std::endl;
	return true;
}

int App::run() {
	// main loop
	SDL_Event event;

	for( ;; ) {

		// handle events
	  while( SDL_PollEvent( &event ) ) {
	    switch( event.type ) {
	    	case SDL_QUIT:  return 0; break; // exit app
	    	case SDL_WINDOWEVENT:
	    		switch (event.window.event) {
	    			case SDL_WINDOWEVENT_RESIZED:
	    				resize(event.window.data1, event.window.data2); 
	    				break; 
	    			break;
	    		}
	      case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: return 0; break; //exit app
						case SDLK_F11: // toggle fullscreen
							if(!isFullscreen){
								SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
								isFullscreen = true;
							} else {
							    SDL_SetWindowFullscreen(m_Window, 0);
							    isFullscreen = false;
							}
							break;
	          }
	          break;
	     }
	  }

		onRender();
		SDL_GL_SwapWindow( m_Window );
		SDL_Delay( 1 );
  }
}

void App::resize(uint width, uint height) {
	glViewport( 0, 0, width, height );	
}

void App::onRender() {
	glDisable( GL_DEPTH_TEST );
	glClearColor( tst, 0.75, 0.0, 0.0 );

	if (tst < 1.0f) {
		tst += 0.01;
	} else {
		tst = .0f;
	}
	glClear( GL_COLOR_BUFFER_BIT );

	m_Renderer->start();
	m_Renderer->push(m_Sprite);
	m_Renderer->stop();
	m_Renderer->flush();

	bool do_abort = false;
  GLenum err = glGetError();
  while( err != GL_NO_ERROR ) {
    std::string error;
		switch(err) {
			case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
			case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
			case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
			case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
			break;
		}
		std::cerr << "OpenGL error: GL_" << error << std::endl;
		err = glGetError();
    do_abort = true;
  }
  if (do_abort)abort();
}

}