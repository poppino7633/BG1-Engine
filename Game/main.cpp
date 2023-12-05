#include <engine.h>
#include <glad/glad.h>

int main() {

  std::shared_ptr<Engine> engine = Engine::Get();

  engine->window->resize(800, 600);

  engine->setBackgroundColor({0.1f, 0.3f, 0.3f, 1.0f});
 
  std::vector<Vertex> vertices = {
    {{-1, -1, 0}, {}, {}, {}},
    {{1, -1, 0}, {}, {}, {}},
    {{0, 1, 0}, {}, {}, {}},
  };
  
  BasicMesh mesh = BasicMesh(vertices, {0, 1, 2});

  while (!engine->shouldStop()) {
    mesh.draw();
    engine->clear();
    engine->window->update();
  }
}
