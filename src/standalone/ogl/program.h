#ifndef PROGRAM_H
#define PROGRAM_H

#include "shader.h"
#include <vector>

namespace ogl {

    /**
     Represents an OpenGL program made by linking shaders.
     */
    class Program { 
    public:
        /**
         Creates a program by linking a list of tdogl::Shader objects
         
         @param shaders  The shaders to link together to make the program
         
         @throws std::exception if an error occurs.
         
         @see tdogl::Shader
         */
        Program(const std::vector<Shader>& shaders);
        ~Program();
        
        
        /**
         @result The program's object id, as returned from glCreateProgram
         */
        GLuint glProgram() const;
        
        
        /**
         @result The attribute index for the given name, as returned from glGetAttribLocation.
         */
        GLint attrib(const GLchar* attribName) const;
        
        
        /**
         @result The uniform index for the given name, as returned from glGetUniformLocation.
         */
        GLint uniform(const GLchar* uniformName) const;

        
    private:
        GLuint _gl_program;
        
        //copying disabled
        Program(const Program&);
        const Program& operator=(const Program&);
    };

}

#endif // PROGRAM_H