#include <string>

class Shader {
protected:
  const unsigned int ID;
  static unsigned int current;
public:
  Shader(std::string vertexPath, std::string fragmentPath);
};
