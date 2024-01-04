#pragma once
#include "log.h"
#include <memory>
#include <filesystem>

class ITexture {
public:
  virtual void bindToUnit(unsigned int unit) = 0;
  virtual unsigned int getID() = 0;
};

class IStaticTexture : public ITexture {};

struct TextureMetadata : public IPrintable {
  enum class Type { t2D, t3D, tCubemap } type;
  size_t maxWidth, maxHeight, maxDepth;
  enum class Format { RGB, RGBA, sRGB, sRGBA, RED } format;
  enum class Filter { Nearest, Linear } filter = Filter::Linear;
  enum class Wrap {
    Repeat,
    RepeatMirror,
    ClampEdge,
    ClampBorder
  } wrapS,
      wrapT, wrapR = Wrap::Repeat;

  TextureMetadata(Type type, size_t width, size_t height, size_t depth,
                  Format format, Filter filter = Filter::Linear,
                  Wrap wrapS = Wrap::Repeat, Wrap wrapT = Wrap::Repeat,
                  Wrap wrapR = Wrap::Repeat)
      : type(type), maxWidth(width), maxHeight(height), maxDepth(depth), format(format),
        filter(filter), wrapS(wrapS), wrapT(wrapT), wrapR(wrapR) {}

  std::string toString() const;
};

struct TextureData {
  std::shared_ptr<unsigned char> data;
  enum class Format { RGB, RGBA, RED } format;
  size_t width, height;
};

class Texture2D : public IStaticTexture, public IPrintable {
protected:
  unsigned int _createTexture2D() const;
  const unsigned int ID;
  const TextureMetadata metadata;
  void _update(){};
  TextureMetadata getMetadataFromData(TextureData data, bool sRGB = 1);

public:
  Texture2D(TextureMetadata metadata, TextureData data = {}); 
  Texture2D(TextureData data, bool sRGB = 1);
  void update(TextureData data, size_t offsetX = 0, size_t offsetY = 0, size_t offsetZ = 0);
  void bindToUnit(unsigned int unit);
  unsigned int getID() { return ID; }
  std::string toString() const;
};


TextureData loadImageData(std::filesystem::path file, bool flip = 1);
