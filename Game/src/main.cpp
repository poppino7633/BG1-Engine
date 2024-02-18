#include <engine.h>
#include <glad/glad.h>
#include <string>

struct testUBO {
  glm::vec4 color;
  glm::vec4 pos;
};

int main() {

  std::cout << Color::Modifier(Color::FG_DEFAULT);

  std::shared_ptr<Engine> engine = Engine::Get();


  engine->window->resize(800, 600);

  engine->setBackgroundColor({0.1f, 0.3f, 0.3f, 1.0f});
 
 /* std::vector<BasicVertex> vertices = {
    {{-0.5f, -0.5f, 0}},
    {{0.5f, -0.5f, 0}},
    {{0, 0.5f, 0}},
  };
  */
  std::shared_ptr<ShaderProgram> program = std::make_shared<ShaderProgram>("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
  
//  BasicMesh mesh = BasicMesh(vertices, {0, 1, 2}, program);

  //Texture2D tex({TextureMetadata::Type::t2D, 1000, 1000, 1, TextureMetadata::Format::RGB}, loadImageData("../assets/textures/container.jpg")); 
  

  //tex.update(loadImageData("../assets/textures/container.jpg"));
  Texture2D tex(loadImageData("../assets/textures/awesomeface.png"), 0);
  auto container = std::make_shared<Texture2D>(loadImageData("../assets/textures/container2.png"), 0);
  auto specular = std::make_shared<Texture2D>(loadImageData("../assets/textures/container2_specular.png"), 0);

  auto mat = std::make_shared<BFMaterial>(container, specular, nullptr); 

  std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0}, {0, 0, 0}, {0.0f, 0.0f}, {0, 0, 0}},
    {{0.5f, -0.5f, 0}, {0, 0, 0}, {1.0f, 0.0f}, {0, 0, 0}},
    {{0.5f, 0.5f, 0}, {0, 0, 0}, {1.0f, 1.0f}, {0, 0, 0}},
    {{-0.5f, 0.5f, 0}, {0, 0, 0}, {0.0f, 1.0f}, {0, 0, 0}},
  };

  Mesh mesh(vertices, {0, 1, 2, 2, 3, 0});
  mesh.shaderProgram = program;
  mesh.material = mat;
   
  UniformBuffer<testUBO> ubo;

  ubo.setData({{0.5f, 0.2f, 0.7f, 1.0f}, {0.2f, 0.8f, 0.5f, 1.0f}});

  ubo.bindToIndex(3);

  console::info(std::to_string(ubo.getData().color.r));

  while (!engine->shouldStop()) {
    engine->clear();
    mesh.draw();
    engine->window->update();
  }

  

  return 0; 

}
