#include <stdexcept>
#include <string>
#include <filesystem>

#include "log.h"

class ShaderCompilationException : public std::runtime_error {
public:
  ShaderCompilationException(std::string message) : runtime_error(message){}
};

class ShaderProgramLinkException : public std::runtime_error {
public:
  ShaderProgramLinkException(std::string message) : runtime_error(message){}
};

class ShaderProgram : IPrintable {
protected:
  const unsigned int ID;
  static unsigned int current;
public:
  class Shader {
  protected:
    const unsigned int ID;
  public:
    enum ShaderType { vertex, fragment };
    Shader(const std::filesystem::path path, const ShaderType type);
    unsigned int getID() const { return ID; }
    ~Shader();
  };
  ShaderProgram(const std::filesystem::path vertexPath, const std::filesystem::path fragmentPath);
  void use() const;
  unsigned int getID() const { return ID; }
  std::string toString() const;
};
