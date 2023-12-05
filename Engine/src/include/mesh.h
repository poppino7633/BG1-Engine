#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "buffer.h"


class IMesh {
public:
  virtual void draw() = 0;
};



class Vertex {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
  glm::vec3 tangent;
};

class VertexBuffer : public ConstBuffer<Vertex> {
public:
  VertexBuffer(const std::vector<Vertex>& vertices) : ConstBuffer<Vertex>(vertices){}
};

class ElementBuffer : public ConstBuffer<unsigned int> {
public:
  ElementBuffer(const std::vector<unsigned int>& indices) : ConstBuffer<unsigned int>(indices){}
};

class VertexArray {
protected:
  unsigned int ID;
  static unsigned int current;
public:
  void use();
  void bindVertexBuffer(const VertexBuffer& buffer);
  void bindElementBuffer(const ElementBuffer& buffer);
  VertexArray();
};

class BasicMesh : public IMesh {
protected:
  VertexArray VAO;
  unsigned int count;

public:
  BasicMesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices);
  void draw();
};
