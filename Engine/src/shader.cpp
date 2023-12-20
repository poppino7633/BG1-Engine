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

ShaderProgram::Shader::Shader(const std::filesystem::path path,
                              const ShaderProgram::Shader::ShaderType type)
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
    console::fatal(ShaderCompilationException("Cannot access shader file at path: " + path.string()));
  };
  const char *codeCStr = code.c_str();
  glShaderSource(ID, 1, &codeCStr, NULL);
  glCompileShader(ID);

  int success;
  std::string infoLog;
  constexpr size_t maxSize = 1024;
  infoLog.reserve(maxSize);
  int size;
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(ID, maxSize, &size, infoLog.data());
    infoLog.resize(size);
    console::fatal(ShaderCompilationException(infoLog));
  } else {
    console::success("Compiled shader ID " + std::to_string(ID));
  }
}

ShaderProgram::Shader::~Shader() {
  console::info("Deleting shader ID " + std::to_string(ID));
  glDeleteShader(ID);
}

ShaderProgram::ShaderProgram(const std::filesystem::path vertexPath, const std::filesystem::path fragmentPath)
    : ID(glCreateProgram()) {
  Shader vertex(vertexPath, Shader::vertex);
  Shader fragment(fragmentPath, Shader::fragment);

  glAttachShader(ID, vertex.getID());
  glAttachShader(ID, fragment.getID());
  glLinkProgram(ID);

  int success;
  std::string infoLog;
  constexpr size_t maxSize = 1024;
  infoLog.reserve(maxSize);
  int size;
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(ID, maxSize, &size, infoLog.data());
    infoLog.resize(size);
    console::fatal(ShaderProgramLinkException(infoLog));
  } else {
    console::success("Linked shader program ID " + std::to_string(ID));
  }
}

void ShaderProgram::use() const {
  if (ID != current) {
    glUseProgram(ID);
    current = ID;
  }
};

std::string ShaderProgram::toString() const {
  return std::string("ShaderProgram: [") + "ID: " + std::to_string(ID) + ", current: " + std::to_string(current) + "]";
}
