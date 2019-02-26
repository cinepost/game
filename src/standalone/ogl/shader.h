#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

namespace ogl {

    /**
     Represents a compiled OpenGL shader.
     */
    class Shader { 
    public:
        
        /**
         Creates a shader from a text file.
         
         @param filePath    The path to the text file containing the shader source.
         @param shaderType  Same as the argument to glCreateShader. For example GL_VERTEX_SHADER
                            or GL_FRAGMENT_SHADER.
         
         @throws std::exception if an error occurs.
         */
        static Shader shaderFromFile(const std::string& filePath, GLenum shaderType);
        
        
        /**
         Creates a shader from a string of shader source code.
         
         @param shaderCode  The source code for the shader.
         @param shaderType  Same as the argument to glCreateShader. For example GL_VERTEX_SHADER
                            or GL_FRAGMENT_SHADER.
         
         @throws std::exception if an error occurs.
         */
        Shader(GLenum shaderType, const std::string& shaderCode);
        
        
        /**
         @result The shader's object ID, as returned from glCreateShader
         */
        GLuint glShader() const;
        
        // Shader objects can be copied and assigned because they are reference counted
        // like a shared pointer
        Shader(const Shader& other);
        Shader& operator =(const Shader& other);
        ~Shader();
        
    private:
        GLuint _object;
        unsigned* _refCount;
        
        void _retain();
        void _release();
    };
    
}

#endif // SHADER_H