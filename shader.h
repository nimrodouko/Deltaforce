#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h> 
#include <string>
#include <sstream>
#include <iostream>

#include <fstream>

class Shader
{
public:

unsigned int shaderprogram;
Shader (const char *vertexpath, const char* fragmentpath);
void use();

// //uniform functions
// void setbool(const std::string &name, bool value) const;
// void setint(const std::string &name, int value) const;
// void setFloat(const std::string &name, float value)const;
};

#endif