#include "gl_sprite.h"

using namespace svq::gfx;

Sprite::Sprite() {
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glGenVertexArrays( 1, &vao );
  glGenBuffers( 1, &vbo );

	width = 0; height = 0;
	mode = GL_RGB;
}

bool Sprite::loadFromImage(std::string fileName) {
	SDL_Surface* surface = IMG_Load(fileName.c_str());

	if (!surface)
	
	if(surface->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
	}

	width = surface->w; height = surface->h;

	// handle texture
	glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

/*
	// handle geometry
	// Put the three triangle vertices (XYZ) and texture coordinates (UV) into the VBO
	GLfloat vertexData[] = {
    //  X     Y     Z       U     V
     0.0f, 0.8f, 0.0f,   0.5f, 1.0f,
    -0.8f,-0.8f, 0.0f,   0.0f, 0.0f,
     0.8f,-0.8f, 0.0f,   1.0f, 0.0f,
	};

	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(program->attrib("vert"));
	glVertexAttribPointer(program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
	// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
	glEnableVertexAttribArray(program->attrib("vertTexCoord"));
	glVertexAttribPointer(program->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

  glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, GL_STATIC_DRAW );
*/
	return true;
}

void Sprite::render(int x, int y) {
	glBindTexture(GL_TEXTURE_2D, tex_id);
	 
	glBindVertexArray( vao );
	glDrawArrays( GL_TRIANGLES, 0, 6 );
}

