#include "include/engine.h"
#include "includes.h"

std::shared_ptr<Engine> Engine::instance(nullptr);

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length, GLchar const *message,
                      void const *user_param) {
  auto const src_str = [source]() {
    switch (source) {
    case GL_DEBUG_SOURCE_API:
      return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      return "WINDOW SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      return "SHADER COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      return "THIRD PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
      return "APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
      return "OTHER";
    default:
      return "";
    }
  }();

  auto const type_str = [type]() {
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      return "ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      return "DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      return "UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
      return "PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
      return "PERFORMANCE";
    case GL_DEBUG_TYPE_MARKER:
      return "MARKER";
    case GL_DEBUG_TYPE_OTHER:
      return "OTHER";
    default:
      return "";
    }
  }();

  auto const severity_str = [severity]() {
    switch (severity) {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return "NOTIFICATION";
    case GL_DEBUG_SEVERITY_LOW:
      return "LOW";
    case GL_DEBUG_SEVERITY_MEDIUM:
      return "MEDIUM";
    case GL_DEBUG_SEVERITY_HIGH:
      return "HIGH";
    default:
      return "";
    }
  }();
  std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id
            << ": " << message << '\n';
}

Engine::Engine() {

  std::cout << "Engine started\n";

  window = std::make_unique<Window>(width, height, "BG1 Demo", 0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw GladException("Failed to load Glad!");
  }
  glViewport(0, 0, width, height);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  glDebugMessageCallback(message_callback, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
}

std::shared_ptr<Engine> Engine::Get() {

  if (instance) {
    return instance;
  } else {
    instance = std::shared_ptr<Engine>(new Engine());
    return instance;
  }
}

void Engine::clear() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Engine::setBackgroundColor(glm::vec4 color) {

  backgroundColor = color;
  glClearColor(color.r, color.g, color.b, color.a);
}

Engine::~Engine() {

  glfwTerminate();

  std::cout << "Engine stopped\n";
}

Window::Window(unsigned int width, unsigned int height, std::string title,
               bool fullscreen) {
  this->width = width;
  this->height = height;
  this->fullscreen = fullscreen;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWmonitor *monitor = nullptr;
  if (fullscreen)
    monitor = glfwGetPrimaryMonitor();

  windowPtr = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
  if (!windowPtr) {
    glfwTerminate();
    throw GLFWException("Cannot create window!");
  }
  glfwMakeContextCurrent((GLFWwindow *)windowPtr);
}

void Window::resize(unsigned int width, unsigned int height) {

  this->width = width;
  this->height = height;

  glfwSetWindowSize((GLFWwindow *)windowPtr, width, height);

  glViewport(0, 0, width, height);
}

bool Window::shouldClose() {
  return glfwWindowShouldClose((GLFWwindow *)windowPtr);
}

void Window::update() {

  glfwSwapBuffers((GLFWwindow *)windowPtr);
  glfwPollEvents();
}

