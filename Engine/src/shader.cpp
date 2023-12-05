#include "include/shader.h"
#include "includes.h"

#include <fstream>
#include <iostream>
#include <sstream>

unsigned int ShaderProgram::current = 0;

unsigned int _createShader(ShaderProgram::Shader::ShaderType type) {
  switch (type) {
  case ShaderProgram::Shader::vertex:
    return glCreateShader(GL_VERTEX_SHADER);
    break;
  case ShaderProgram::Shader::fragment:
    return glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    throw;
    break;
  };
}

ShaderProgram::Shader::Shader(std::string path,
                              ShaderProgram::Shader::ShaderType type)
    : ID(_createShader(type)) {
  std::string code;
  std::ifstream file;

  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(path);
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    code = ss.str();

  } catch (std::ifstream::failure e) {
    std::cout << "SHADER ERROR"
              << "\n";
    throw;
  };
  const char *codeCStr = code.c_str();
  glShaderSource(ID, 1, &codeCStr, NULL);
  glCompileShader(ID);

  int success;
  std::string infoLog;
  const unsigned int maxSize = 1024;
  infoLog.reserve(maxSize);
  int size;
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

  if (!success) {
    std::cout << "SHADER COMPILATION ERROR\n";
    glGetShaderInfoLog(ID, maxSize, &size, infoLog.data());
    infoLog.resize(size);
    std::cout << infoLog << "\n";
    throw;
  }
}

ShaderProgram::Shader::~Shader() {
  std::cout << "Deleting shader ( ID " << ID << " )\n";
  glDeleteShader(ID);
}

ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
    : ID(glCreateProgram()) {
  Shader vertex(vertexPath, Shader::vertex);
  Shader fragment(fragmentPath, Shader::fragment);

  glAttachShader(ID, vertex.getID());
  glAttachShader(ID, fragment.getID());
  glLinkProgram(ID);

  int success;
  std::string infoLog;
  const unsigned int maxSize = 1024;
  infoLog.reserve(maxSize);
  int size;
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(ID, maxSize, &size, infoLog.data());
    infoLog.resize(size);
    std::cout << infoLog << "\n";
    throw;
  }
}

void ShaderProgram::use() const {
  if (ID != current) {
    std::cout << "Switching shader program from ID " << current << " to ID "
              << ID << "\n";
    glUseProgram(ID);
    current = ID;
  }
};
