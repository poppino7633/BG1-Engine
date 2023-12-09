#include "include/mesh.h"
#include "includes.h"
#include <iostream>

unsigned int VertexArray::current = 0;

VertexArray::VertexArray() { 
  glCreateVertexArrays(1, &ID);
}

template <typename T>
void VertexArray::bindVertexBuffer(const VertexBuffer<T> &buffer) {
  size_t size = T::getSize();
  glVertexArrayVertexBuffer(ID, 0, buffer.getID(), 0, size);

  std::vector<VertexAttribute> attributes = T::getAttributes();

  for (VertexAttribute a : attributes) {
    glEnableVertexArrayAttrib(ID, a.index);
    GLenum type = GL_FLOAT;
    glVertexArrayAttribFormat(ID, a.index, a.numComponents, type, GL_FALSE,
                              a.offset);
    glVertexArrayAttribBinding(ID, a.index, 0);
  }
}

void VertexArray::bindElementBuffer(const ElementBuffer &buffer) {
  glVertexArrayElementBuffer(ID, buffer.getID());
}

void VertexArray::use() {
  if (ID != current) {
    glBindVertexArray(ID);
    current = ID;
  }
};

BasicMesh::BasicMesh(const std::vector<BasicVertex> &vertices,
                     const std::vector<unsigned int> &indices,
                     const std::shared_ptr<ShaderProgram> shaderProgram)
    : count(indices.size()), shaderProgram(shaderProgram) {
  VAO = VertexArray();
  VertexBuffer<BasicVertex> VBO(vertices);
  ElementBuffer EBO(indices);

  VAO.bindVertexBuffer(VBO);
  VAO.bindElementBuffer(EBO);
}

void BasicMesh::draw() {
  VAO.use();
  shaderProgram->use();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices,
           const std::shared_ptr<ShaderProgram> shaderProgram)
    : count(indices.size()), shaderProgram(shaderProgram) {
  VAO = VertexArray();
  VertexBuffer<Vertex> VBO(vertices);
  ElementBuffer EBO(indices);

  VAO.bindVertexBuffer(VBO);
  VAO.bindElementBuffer(EBO);
}

void Mesh::draw() {
  VAO.use();
  shaderProgram->use();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
};
