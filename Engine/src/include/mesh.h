#include <glm/glm.hpp>
#include <vector>
#include <memory>

class Vertex {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
  glm::vec3 tangent;
};

class IMesh {
public:
  virtual void draw() = 0;
};

class IBuffer {
protected:
  unsigned int ID;
  virtual void updateSubData(size_t offset, size_t size, const void* data) = 0;
public:
  unsigned int getID() { return ID; } 
};

template<typename T>
class StaticBuffer : public IBuffer {
protected:
  void updateSubData(size_t offset, size_t size, const void* data);
  const size_t size;
public:
  StaticBuffer<T>(const std::vector<T>& data);
  StaticBuffer<T>(unsigned int count);
  void update(unsigned int offset, typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end);
};

class DynamicBuffer : public IBuffer {
protected:
  void updateSubData(size_t offset, size_t size, const void* data);
  size_t size;
public:
  DynamicBuffer();

  template<typename T>
  DynamicBuffer(unsigned int count);

  template<typename T>
  DynamicBuffer(const std::vector<T>& data);

  template<typename T>
  void reallocate(unsigned int count);
  template<typename T>
  void reallocate(const std::vector<T>& data);

  template<typename T>
  void update(unsigned int offset, typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end);

};


class VertexArray {
protected:
  unsigned int ID;
  static std::unique_ptr<VertexArray> current;
public:
  void use();
  VertexArray();
  void bindVertexBuffer(IBuffer& buffer);
  void bindElementBuffer(IBuffer& buffer);

};


class BasicMesh : public IMesh {
protected:
  VertexArray VAO;
  std::unique_ptr<IBuffer> VBO;
  std::unique_ptr<IBuffer> EBO;
  unsigned int count;
public:
  BasicMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
  void draw();
};
