#include <engine.h>
#include <glad/glad.h>

int main() {

  std::shared_ptr<Engine> engine = Engine::Get();

  engine->window->resize(800, 600);

  engine->setBackgroundColor({0.1f, 0.3f, 0.3f, 1.0f});
 
  std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0}, {}, {}, {}},
    {{0.5f, -0.5f, 0}, {}, {}, {}},
    {{0, 0.5f, 0}, {}, {}, {}},
  };
  std::shared_ptr<ShaderProgram> program = std::make_shared<ShaderProgram>("resources/shaders/basic.vert", "resources/shaders/basic.frag");
  
  BasicMesh mesh = BasicMesh(vertices, {0, 1, 2}, program);

  while (!engine->shouldStop()) {
    engine->clear();
    mesh.draw();
    engine->window->update();
  }
}