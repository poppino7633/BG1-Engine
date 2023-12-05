#include <string>

class ShaderProgram {
protected:
  const unsigned int ID;
  static unsigned int current;
public:
  class Shader {
  protected:
    const unsigned int ID;
  public:
    enum ShaderType { vertex, fragment };
    Shader(std::string path, ShaderType type);
    unsigned int getID() const { return ID; }
    ~Shader();
  };
  ShaderProgram(std::string vertexPath, std::string fragmentPath);
  void use() const;
  unsigned int getID() const { return ID; }
};
