#include <stdexcept>

#include "svq/gfx/ogl/gl_program.h"

using namespace svq::gfx;

Program::Program(const std::vector<Shader>& shaders) : _gl_program(0) {
    if(shaders.size() <= 0)
        throw std::runtime_error("No shaders were provided to create the program");
    
    //create the program object
    _gl_program = glCreateProgram();
    if(_gl_program == 0)
        throw std::runtime_error("glCreateProgram failed");
    
    // attach all the shaders
    for(unsigned i = 0; i < shaders.size(); ++i)
        glAttachShader(_gl_program, shaders[i].glShader());
    
    //link the shaders together
    glLinkProgram(_gl_program);
    
    //throw exception if linking failed
    GLint status;
    glGetProgramiv(_gl_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");
        
        GLint infoLogLength;
        glGetProgramiv(_gl_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(_gl_program, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteProgram(_gl_program); _gl_program = 0;
        throw std::runtime_error(msg);
    }
}

Program::~Program() {
    //might be 0 if ctor fails by throwing exception
    if(_gl_program != 0) glDeleteProgram(_gl_program);
}

GLuint Program::glProgram() const {
    return _gl_program;
}

GLint Program::attrib(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName was NULL");
    
    GLint attrib = glGetAttribLocation(_gl_program, attribName);
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
    
    return attrib;
}

GLint Program::uniform(const GLchar* uniformName) const {
    if(!uniformName)
        throw std::runtime_error("uniformName was NULL");
    
    GLint uniform = glGetUniformLocation(_gl_program, uniformName);
    if(uniform == -1)
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);
    
    return uniform;
}