#include <string> 
#include <iostream> 
#include <sstream>
#include <fstream>
#include <streambuf> 

//#include <boost/tokenizer.hpp>
//#include <boost/token_iterator.hpp>

#include "svq/gfx/ogl/gl_common.h"
#include "svq/gfx/ogl/gl_shader.h"

namespace svq{ namespace gfx{

enum class GL_ShaderType {
	UNKNOWN = -1, 
	VERTEX = 0, 
	FRAGMENT = 1
};


GL_Shader::GL_Shader(const std::string& name, const std::string& shaderSourcePath) : m_Name(name) {
	m_Sources = parseSources(shaderSourcePath);
	init();
}

GL_Shader::GL_Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name(name) {
	m_Sources.vertexSource = vertexSource;
	m_Sources.fragmentSource = fragmentSource;
	init();
}

GL_Shader::~GL_Shader() { }

void GL_Shader::init() {
	//m_VSUserUniformBuffer = nullptr;
	//m_PSUserUniformBuffer = nullptr;

	GLShaderErrorInfo error;
	m_Handle = compile(m_Sources, error);
	if (!m_Handle)
		std::cerr << error.message[error.shader] << std::endl;
	assert(m_Handle);
	//ResolveUniforms();
	//ValidateUniforms();
}

void GL_Shader::shutdown() {
	GL_CALL(glDeleteProgram(m_Handle));
}

ShaderSources GL_Shader::parseSources(const std::string& shaderSourcePath) {
	GL_ShaderType type = GL_ShaderType::UNKNOWN;
	std::string line;
	std::stringstream shaderSources[2];

	std::ifstream stream(shaderSourcePath);

	while (std::getline(stream, line)) {
		if (line.find("#shader ") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = GL_ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = GL_ShaderType::FRAGMENT;	
		} else {
			shaderSources[(int)type] << line << std::endl;
		}
	}

	return {shaderSources[0].str(), shaderSources[1].str()};
}

uint GL_Shader::compile(ShaderSources sources, GLShaderErrorInfo error) {
	const char* vertexSource = sources.vertexSource.c_str();
	const char* fragmentSource = sources.fragmentSource.c_str();

	GL_CALL(uint program = glCreateProgram());
	GL_CALL(GLuint vertex = glCreateShader(GL_VERTEX_SHADER));
	GL_CALL(GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER));

	GL_CALL(glShaderSource(vertex, 1, &vertexSource, NULL));
	GL_CALL(glCompileShader(vertex));

	GLint result;
	GL_CALL(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		std::cerr << "Failed to compile vertex shader" << std::endl;
		GL_CALL(glDeleteShader(vertex));
		return 0;
	}

	GL_CALL(glShaderSource(fragment, 1, &fragmentSource, NULL));
	GL_CALL(glCompileShader(fragment));

	GL_CALL(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		std::cerr << "Failed to compile fragment shader" << std::endl;
		GL_CALL(glDeleteShader(fragment));
		return 0;
	}

	GL_CALL(glAttachShader(program, vertex));
	GL_CALL(glAttachShader(program, fragment));

	GL_CALL(glLinkProgram(program));
	GL_CALL(glValidateProgram(program));

	GL_CALL(glDetachShader(program, vertex));
	GL_CALL(glDetachShader(program, fragment));

	GL_CALL(glDeleteShader(vertex));
	GL_CALL(glDeleteShader(fragment));

	return program;
}

void GL_Shader::bind() const {
	GL_CALL(glUseProgram(m_Handle));
}

void GL_Shader::unbind() const {
	GL_CALL(glUseProgram(0));
}

const void GL_Shader::setUnifromMatrix4fv(const std::string &uniform_name, const void *value) const {
	GLint uniform_location = glGetUniformLocation(m_Handle, uniform_name.c_str());
	GLenum err = glGetError();
  	
	GL_CALL(glUseProgram(m_Handle));
	GL_CALL(glUniformMatrix4fv(uniform_location, 1, GL_FALSE, (const GLfloat *)value));
	
}

}}