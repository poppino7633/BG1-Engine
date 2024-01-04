#include <glm/glm.hpp>
#include <memory>

#include "mesh.h"

class GLFWException : public std::runtime_error {
public:
  GLFWException(std::string message) : runtime_error(message) {}
};

class GladException : public std::runtime_error {
public:
  GladException(std::string message) : runtime_error(message) {}
};

class Window {

protected:
  void* windowPtr;
  unsigned int width, height;
  bool fullscreen;

public:
  Window(unsigned int width, unsigned int height, std::string title,
         bool fullscreen);
  void resize(unsigned int width, unsigned int height);
  bool shouldClose();
  void update();
};

class Engine {

protected:
  static std::weak_ptr<Engine> instance;

  Engine();

  unsigned int width = 100;
  unsigned int height = 100;

  glm::vec4 backgroundColor;

public:
  static std::shared_ptr<Engine> Get();
  std::unique_ptr<Window> window;
  bool shouldStop() { return window->shouldClose(); };
  void clear();

  void setBackgroundColor(glm::vec4 color);

  ~Engine();
};
