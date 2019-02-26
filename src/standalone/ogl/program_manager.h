#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#include "program.h"

namespace ogl {


class Program_Manager {
  public:
    Program_Manager(void);
    ~Program_Manager(void);

    bool createProgram(const std::string& programName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
    static Program *getProgram(const std::string&);

  private:
  	std::string ResourcePath(std::string fileName);
    static std::map<std::string, Program*> programs;
};

}

#endif // PROGRAM_MANAGER_H