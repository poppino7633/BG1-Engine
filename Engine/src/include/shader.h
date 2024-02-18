#include <filesystem>
#include <stdexcept>
#include <string>

#include "buffer.h"
#include "log.h"


class ShaderCompilationException : public std::runtime_error {
public:
  ShaderCompilationException(std::string message) : runtime_error(message) {}
};

class ShaderProgramLinkException : public std::runtime_error {
public:
  ShaderProgramLinkException(std::string message) : runtime_error(message) {}
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
  ShaderProgram(const std::filesystem::path vertexPath,
                const std::filesystem::path fragmentPath);
  void use() const;
  unsigned int getID() const { return ID; }
  std::string toString() const;
};

template <typename T> class UniformBuffer : public StaticBuffer<T> {
protected:
  T data;

  void _bindIndex(unsigned int ID, unsigned int index);

public:
  UniformBuffer() : StaticBuffer<T>(1) {

  };
  T getData() { return data; }
  void setData(T data) {
    this->data = data;
    this->update(0, {data}); 
  };
  void bindToIndex(unsigned int index) {
    this->_bindUBOBase(this->getID(), index);
  };
};
