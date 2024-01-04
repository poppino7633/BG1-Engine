#pragma once
#include <iostream>
#include <vector>

class IBuffer {
protected:
  virtual void _read(size_t offset, size_t size, void *data) = 0;
  unsigned int _createConstBuffer(size_t size, const void *data);
  unsigned int _createStaticBuffer(size_t size, const void *data);
  unsigned int _createDynamicBuffer();
  void _reallocateBuffer(unsigned int ID, size_t size, const void *data);
  void _updateBuffer(unsigned int ID, size_t offset, size_t size,
                     const void *data);
  void _readBuffer(unsigned int ID, size_t offset, size_t size,
                   void *destination);
};


class BufferOutOfRangeException : public std::runtime_error {
public:
  BufferOutOfRangeException(std::string message) : runtime_error(message) {}
};

template <typename T> class ConstBuffer : public IBuffer {
protected:
  void _read(size_t offset, size_t size, void *data) {
    _readBuffer(ID, offset, size, data);
  }
  const unsigned int count;
  const unsigned int ID;

public:
  ConstBuffer<T>(const std::vector<T> data)
      : ID(_createConstBuffer(data.size() * sizeof(T), data.data())),
        count(data.size()) {}

  void read(std::vector<T> &destination) {
    destination.resize(count);
    _read(0, count * sizeof(T), destination.data());
  }
  std::vector<T> read() {
    std::vector<T> destination;
    destination.resize(count);
    _read(0, count * sizeof(T), destination.data());
    return destination;
  }
  unsigned int getCount() const { return count; }
  unsigned int getID() const { return ID; }
};

template <typename T> class StaticBuffer : public IBuffer {
protected:
  void _read(size_t offset, size_t size, void *data) {
    _readBuffer(ID, offset, size, data);
  }
  const unsigned int count;
  const unsigned int ID;

public:
  StaticBuffer<T>(const std::vector<T> &data) : ID(_createStaticBuffer(data.size() * sizeof(T), data.data())), count(data.size()) {}
  StaticBuffer<T>(unsigned int count) : ID(_createStaticBuffer(count * sizeof(T), nullptr)), count(count) {}
  void read(std::vector<T> &destination) {
    destination.resize(count);
    _read(0, count * sizeof(T), destination.data());
  }
  std::vector<T> read() {
    std::vector<T> destination;
    destination.resize(count);
    _read(0, count * sizeof(T), destination.data());
    return destination;
  }
  void update(unsigned int offset, const std::vector<T> &data) {
    if (offset + data.size() > count) {
      std::string message;
      message += "Cannot resize static buffer ( ID ";
      message += std::to_string(ID);
      message += " ) of ";
      message += std::to_string(count);
      message += " elements to new size of ";
      message += std::to_string(offset + data.size());
      message += " elements\n";
      throw BufferOutOfRangeException(message);
    }
    _updateBuffer(ID, offset * sizeof(T), data.size() * sizeof(T), data.data());
  }
  void replace(const std::vector<T> &data) {
    _reallocateBuffer(ID, data.size() * sizeof(T), data.data());
  }
  unsigned int getCount() const { return count; }
  unsigned int getID() const { return ID; }
};

template <typename T> class DynamicBuffer : public IBuffer {
protected:
  void _read(size_t offset, size_t size, void *data) {
    _readBuffer(ID, offset, size, data);
  }
  unsigned int count;
  const unsigned int ID;

public:
  DynamicBuffer<T>(const std::vector<T> &data) : ID(_createDynamicBuffer()), count(data.size()) {
    _reallocateBuffer(ID, data.size() * sizeof(T), data.data());
  }
  DynamicBuffer<T>(unsigned int count) : ID(_createDynamicBuffer()), count(count) {
    _reallocateBuffer(ID, count * sizeof(T), nullptr);
  }
  void read(std::vector<T> &destination) {
    destination.resize(count);
    _read(0, count * sizeof(T), destination.data());
  }
  std::vector<T> read() {
    std::vector<T> destination;
    destination.resize(count);
    _read(0, count * sizeof(T), destination.data());
    return destination;
  }
  void update(unsigned int offset, const std::vector<T> &data) {
    if (offset + data.size() > count) {
      std::cout << "WARNING: Reallocating buffer (ID " << ID << ") count "
                << count << " -> ";

      std::vector<T> startData = read();
      startData.resize(offset + data.size());
      std::copy(data.begin(), data.end(), startData.begin() + offset);

      count = offset + data.size();
      std::cout << "New count: " << count << "\n";
      _reallocateBuffer(ID, count * sizeof(T), startData.data());
      return;
    }

    _updateBuffer(ID, offset * sizeof(T), data.size() * sizeof(T), data.data());
  }
  void replace(const std::vector<T> &data) {
    _reallocateBuffer(ID, data.size() * sizeof(T), data.data());
    count = data.size();
  }
  unsigned int getCount() const { return count; }
  unsigned int getID() const { return ID; }
};
