#include "gl_program_manager.h"
 
using namespace svq::gfx;
 
//don't forget about this little static guy in cpp
std::map<std::string, Program*> Program_Manager::programs;

 
Program_Manager::Program_Manager(void) {
//same
}
 
//destructor delete programs
Program_Manager::~Program_Manager(void) {
 
   std::map<std::string, Program*>::iterator i;
   for (i = programs.begin();i != programs.end(); ++i)
      {
        GLuint pr = i->second->glProgram();
        glDeleteProgram(pr);
      }
    programs.clear();
}

std::string Program_Manager::ResourcePath(std::string fileName) {
  // quick development hack to locate resources dir
  #ifdef _GAME_RESOURCES_DIR
    return _GAME_RESOURCES_DIR + fileName;
  #else
    return fileName;
  #endif
}
 
bool Program_Manager::createProgram(const std::string& programName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) {
    std::cout << "creating opengl program: " << programName << std::endl;
    
    std::vector<Shader> shaders;
    shaders.push_back(Shader::shaderFromFile(ResourcePath(vertexShaderFilename.c_str()), GL_VERTEX_SHADER));
    shaders.push_back(Shader::shaderFromFile(ResourcePath(fragmentShaderFilename.c_str()), GL_FRAGMENT_SHADER));

    programs[programName] = new Program(shaders);
    return true;
}
 
//the new method used to get the program
Program *Program_Manager::getProgram(const std::string& programName) {
    //make sure that you check if program exist first
    //before you return it
    return programs.at(programName);
 
}
