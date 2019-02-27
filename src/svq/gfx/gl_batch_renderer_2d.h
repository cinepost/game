#ifndef GL_BATCH_RENDERER__H
#define GL_BATCH_RENDERER__H

#include <iostream>
#include <string>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#include "svq/gfx/renderer_2d.h"

namespace svq { namespace gfx {

#define RENDERER_MAX_SPRITES    10000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6 

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX  1

    class GL_BatchRenderer_2D : public Renderer2D { 
    public:
        GL_BatchRenderer_2D();
        ~GL_BatchRenderer_2D();

        void start();
        void stop();
        void push(const GL_Renderable2D* renderable) override;
        void flush() override;
        
    private:
        GLuint m_VBO, m_VAO;
        GLsizei m_IndexCount;
    };
    
} }

#endif // GL_BATCH_RENDERER__H