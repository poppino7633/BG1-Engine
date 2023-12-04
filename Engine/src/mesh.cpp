#include "include/mesh.h"
#include "includes.h"
#include <iostream>

template <typename T>
void StaticBuffer<T>::updateSubData(size_t offset, size_t size,
                                    const void *data) {
  if (size > this->size)
    throw;
  glNamedBufferSubData(ID, offset, size, data);
}

template <typename T>
StaticBuffer<T>::StaticBuffer(const std::vector<T> &data)
    : size(data.size() * sizeof(T)) {

  glCreateBuffers(1, &ID);
  glNamedBufferStorage(ID, data.size() * sizeof(T), data.data(),
                       GL_DYNAMIC_STORAGE_BIT);
}

template <typename T>
StaticBuffer<T>::StaticBuffer(unsigned int count) : size(count * sizeof(T)) {
  glCreateBuffers(1, &ID);
  glNamedBufferStorage(ID, size * sizeof(T), nullptr, GL_DYNAMIC_STORAGE_BIT);
}

template <typename T>
StaticBuffer<T> update(unsigned int offset,
                       typename std::vector<T>::iterator begin,
                       typename std::vector<T>::iterator end) {
  updateSubData(offset, (end - begin) * sizeof(T), &(*begin));
}

void DynamicBuffer::updateSubData(size_t offset, size_t size,
                                  const void *data) {
  if (size > this->size)
    throw;
  glNamedBufferSubData(ID, offset, size, data);
}

DynamicBuffer::DynamicBuffer() {
  glCreateBuffers(1, &ID);
  size = 0;
}

template <typename T> DynamicBuffer::DynamicBuffer(unsigned int count) {
  glCreateBuffers(1, &ID);
  glNamedBufferData(ID, count * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
  size = count * sizeof(T);
}

template <typename T> DynamicBuffer::DynamicBuffer(const std::vector<T> &data) {

  glCreateBuffers(1, &ID);
  glNamedBufferData(ID, data.size() * sizeof(T), data.data(), GL_DYNAMIC_DRAW);
  size = data.size() * sizeof(T);
}

template <typename T> void DynamicBuffer::reallocate(unsigned int count) {
  glNamedBufferData(ID, count * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
  size = count * sizeof(T);
}

template <typename T>
void DynamicBuffer::reallocate(const std::vector<T> &data) {
  glNamedBufferData(ID, data.size() * sizeof(T), data.data(), GL_DYNAMIC_DRAW);
  size = data.size() * sizeof(T);
}

template <typename T>
void DynamicBuffer::update(unsigned int offset,
                           typename std::vector<T>::iterator begin,
                           typename std::vector<T>::iterator end) {
  updateSubData(offset * sizeof(T), (end - begin) * sizeof(T), &(*begin));
}

std::unique_ptr<VertexArray> VertexArray::current;

void VertexArray::use() {
  if (this == current.get())
    return;

  current.reset(this);
  glBindVertexArray(ID);
}

VertexArray::VertexArray() { glCreateVertexArrays(1, &ID); }

BasicMesh::BasicMesh(const std::vector<Vertex> &vertices,
                     const std::vector<unsigned int> &indices) {
  VBO = std::make_unique<StaticBuffer<Vertex>>(vertices);
  EBO = std::make_unique<StaticBuffer<unsigned int>>(indices);
}

void BasicMesh::draw() {
  VAO.use();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
