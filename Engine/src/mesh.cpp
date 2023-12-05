#include "include/mesh.h"
#include "includes.h"
#include <iostream>

unsigned int VertexArray::current = 0;

VertexArray::VertexArray() {
  glCreateVertexArrays(1, &ID);

  glEnableVertexArrayAttrib(ID, 0);
  glEnableVertexArrayAttrib(ID, 1);
  glEnableVertexArrayAttrib(ID, 2);
  glEnableVertexArrayAttrib(ID, 3);

  glVertexArrayAttribFormat(ID, 0, 3, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex, position));
  glVertexArrayAttribFormat(ID, 1, 3, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex, normal));
  glVertexArrayAttribFormat(ID, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
  glVertexArrayAttribFormat(ID, 3, 3, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex, tangent));

  glVertexArrayAttribBinding(ID, 0, 0);
  glVertexArrayAttribBinding(ID, 1, 0);
  glVertexArrayAttribBinding(ID, 2, 0);
  glVertexArrayAttribBinding(ID, 3, 0);
}

void VertexArray::bindVertexBuffer(const VertexBuffer &buffer) {
  glVertexArrayVertexBuffer(ID, 0, buffer.getID(), 0, sizeof(Vertex));
}

void VertexArray::bindElementBuffer(const ElementBuffer &buffer) {
  glVertexArrayElementBuffer(ID, buffer.getID());
}

void VertexArray::use() {
  if (ID != current) {
    std::cout << "Changing VAO from " << current << " to " << ID << "\n";
    glBindVertexArray(ID);
    current = ID;
  }
};

BasicMesh::BasicMesh(const std::vector<Vertex> &vertices,
                     const std::vector<unsigned int> &indices,
                     std::shared_ptr<ShaderProgram> shaderProgram) : shaderProgram(shaderProgram) {
  VAO = VertexArray();
  VertexBuffer VBO(vertices);
  ElementBuffer EBO(indices);

  count = indices.size();

  VAO.bindVertexBuffer(VBO);
  VAO.bindElementBuffer(EBO);
}

void BasicMesh::draw() {
  VAO.use();
  shaderProgram->use();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
