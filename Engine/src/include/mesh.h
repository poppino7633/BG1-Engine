#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "log.h"
#include "buffer.h"
#include "shader.h"

class IMesh {
public:
  virtual void draw() = 0;
};

struct VertexAttribute {
  enum Type { f32, i32 };
  Type type;
  unsigned int index;
  size_t offset;
  unsigned int numComponents;
};

class BasicVertex {
public:
  glm::vec3 position;
  static constexpr size_t getSize() { return sizeof(position); }
  static const std::vector<VertexAttribute> getAttributes() {
    return {
        {VertexAttribute::f32, 0, offsetof(BasicVertex, position), 3},

    };
  }
};

class Vertex {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
  glm::vec3 tangent;
  static constexpr size_t getSize() { return sizeof(position) + sizeof(normal) + sizeof(uv) + sizeof(tangent);}
  static const std::vector<VertexAttribute> getAttributes() {
    return  {
      {VertexAttribute::f32, 0, offsetof(Vertex, position), 3},
      {VertexAttribute::f32, 1, offsetof(Vertex, normal), 3},
      {VertexAttribute::f32, 2, offsetof(Vertex, uv), 2},
      {VertexAttribute::f32, 3, offsetof(Vertex, tangent), 3},
    };
  }
};

template <typename T> class VertexBuffer : public ConstBuffer<T> {
public:
  VertexBuffer<T>(const std::vector<T> &vertices) : ConstBuffer<T>(vertices) {}
};

class ElementBuffer : public ConstBuffer<unsigned int> {
public:
  ElementBuffer(const std::vector<unsigned int> &indices)
      : ConstBuffer<unsigned int>(indices) {}
};

class VertexArray {
protected:
  unsigned int ID;
  static unsigned int current;

public:
  void use();
  template <typename T> void bindVertexBuffer(const VertexBuffer<T> &buffer);
  void bindElementBuffer(const ElementBuffer &buffer);
  VertexArray();
};

class BasicMesh : public IMesh {
protected:
  VertexArray VAO;
  const unsigned int count;

public:
  BasicMesh(const std::vector<BasicVertex> &vertices,
            const std::vector<unsigned int> &indices,
            const std::shared_ptr<ShaderProgram> shaderProgram);
  std::shared_ptr<ShaderProgram> shaderProgram;
  void draw();
};

class Mesh : public IMesh {
protected:
  VertexArray VAO;
  const unsigned int count;
  

public:
  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<unsigned int> &indices,
       const std::shared_ptr<ShaderProgram> shaderProgram);
  std::shared_ptr<ShaderProgram> shaderProgram;
  void draw();
};
