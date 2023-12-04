#include <engine.h>

int main() {

  std::shared_ptr<Engine> engine = Engine::Get();

  engine->window->resize(800, 600);

  engine->setBackgroundColor({0.1f, 0.3f, 0.3f, 1.0f});
 
  StaticBuffer<unsigned int> buffer({1, 2, 3, 4, 5});
  std::vector<unsigned int> u = {9, 10, 11};
  buffer.update(2, u.begin(), u.end());

  while (!engine->shouldStop()) {
    engine->clear();
    engine->window->update();
  }
}
