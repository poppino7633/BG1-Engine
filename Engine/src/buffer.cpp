#include "include/buffer.h"
#include "includes.h"

void IBuffer::_reallocateBuffer(unsigned int ID, size_t size, const void *data){
  glNamedBufferData(ID, size, data, GL_DYNAMIC_DRAW);
}

void IBuffer::_updateBuffer(unsigned int ID, size_t offset, size_t size, const void *data){
  glNamedBufferSubData(ID, offset, size, data);
}

void IBuffer::_readBuffer(unsigned int ID, size_t offset, size_t size, void *destination){
  glGetNamedBufferSubData(ID, offset, size, destination);
}

unsigned int IBuffer::_createConstBuffer(size_t size, const void *data){
  unsigned int buffer;
  glCreateBuffers(1, &buffer);
  glNamedBufferStorage(buffer, size, data, 0);
  return buffer;
}

unsigned int IBuffer::_createStaticBuffer(size_t size, const void* data){
  unsigned int buffer;
  glCreateBuffers(1, &buffer);
  glNamedBufferStorage(buffer, size, data, GL_DYNAMIC_STORAGE_BIT);
  return buffer;
}


unsigned int IBuffer::_createDynamicBuffer(){
  unsigned int buffer;
  glCreateBuffers(1, &buffer);
  return buffer;
}
