#include "include/texture.h"
#include "includes.h"
#include <string>
#include <stb_image.h>


std::string TextureMetadata::toString() const {

  std::string typeStr = "Type: ";
  switch(type) {
    case Type::t2D:
    typeStr += "2D";
    break;
    case Type::t3D:
    typeStr += "3D";
    break;
    case Type::tCubemap:
    typeStr += "Cubemap";
    break;
  }

  std::string formatStr = "Format: ";
  switch(format){
    case Format::RGB:
    formatStr += "RGB";
    break;
    case Format::RGBA:
    formatStr += "RGBA";
    break;
    case Format::sRGB:
    formatStr += "sRGB";
    break;
    case Format::sRGBA:
    formatStr += "sRGBA";
    break;
    case Format::RED:
    formatStr += "RED";
    break;
  }

  return "   " + typeStr + "\n   " + formatStr + "\n";

}


unsigned int Texture2D::_createTexture2D() const {
  unsigned int ID;
  glCreateTextures(GL_TEXTURE_2D, 1, &ID);
  return ID;
}

struct GLmeta { GLenum format, filter, wrapS, wrapT; }; 
GLmeta getGLmeta(TextureMetadata metadata){ 
  GLenum format, filter, wrapS, wrapT;
  switch(metadata.wrapS){
    case TextureMetadata::Wrap::Repeat: wrapS = GL_REPEAT; break;
    case TextureMetadata::Wrap::RepeatMirror: wrapS = GL_MIRRORED_REPEAT; break;
    case TextureMetadata::Wrap::ClampEdge: wrapS = GL_CLAMP_TO_EDGE; break;
    case TextureMetadata::Wrap::ClampBorder: wrapS = GL_CLAMP_TO_BORDER; break;
  }
  switch(metadata.wrapT){
    case TextureMetadata::Wrap::Repeat: wrapT = GL_REPEAT; break;
    case TextureMetadata::Wrap::RepeatMirror: wrapT = GL_MIRRORED_REPEAT; break;
    case TextureMetadata::Wrap::ClampEdge: wrapT = GL_CLAMP_TO_EDGE; break;
    case TextureMetadata::Wrap::ClampBorder: wrapT = GL_CLAMP_TO_BORDER; break;
  }

  switch(metadata.filter){
    case TextureMetadata::Filter::Nearest: filter = GL_NEAREST; break;
    case TextureMetadata::Filter::Linear: filter = GL_LINEAR; break;
  }

  switch(metadata.format) {
    case TextureMetadata::Format::RGB: format = GL_RGB8; break;
    case TextureMetadata::Format::RGBA: format = GL_RGBA8; break;
    case TextureMetadata::Format::sRGB: format = GL_SRGB8; break;
    case TextureMetadata::Format::sRGBA: format = GL_SRGB8_ALPHA8; break;
    case TextureMetadata::Format::RED: format = GL_R8; break;
  }
  return GLmeta { format, filter, wrapS, wrapT };
}

Texture2D::Texture2D(TextureMetadata metadata, TextureData data) : ID(_createTexture2D()), metadata(metadata) {

  GLmeta meta = getGLmeta(metadata);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_S, meta.wrapS);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_T, meta.wrapT);
  glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, meta.filter);
  glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, meta.filter);
  glTextureStorage2D(ID, 1, meta.format, metadata.maxWidth, metadata.maxHeight);
  if(data.data) {
    update(data);  
  }

};

TextureMetadata Texture2D::getMetadataFromData(TextureData data, bool sRGB) {
  TextureMetadata::Format format;
  
  switch(data.format){
  case TextureData::Format::RED:
    format = TextureMetadata::Format::RED;   
    break;
  case TextureData::Format::RGB:
    if(sRGB) format = TextureMetadata::Format::sRGB; else format = TextureMetadata::Format::RGB;
    break;
  case TextureData::Format::RGBA:
    if(sRGB) format = TextureMetadata::Format::sRGBA; else format = TextureMetadata::Format::RGBA;
    break;
  }

  return TextureMetadata(TextureMetadata::Type::t2D, data.width, data.height, 1, format);
}

Texture2D::Texture2D(TextureData data, bool sRGB) : ID(_createTexture2D()), metadata(getMetadataFromData(data, sRGB)){

  GLmeta meta = getGLmeta(metadata);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_S, meta.wrapS);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_T, meta.wrapT);
  glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, meta.filter);
  glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, meta.filter);
  glTextureStorage2D(ID, 1, meta.format, metadata.maxWidth, metadata.maxHeight);
  update(data);
}

void Texture2D::update(TextureData data, size_t offsetX, size_t offsetY, size_t offsetZ){

  if(offsetX + data.width > metadata.maxWidth) throw;
  if(offsetY + data.height > metadata.maxHeight) throw;

  GLenum format;
  switch(data.format) {
  case TextureData::Format::RGB:  
    if(metadata.format == TextureMetadata::Format::RGB || metadata.format == TextureMetadata::Format::sRGB) {
      format = GL_RGB; 
    } else {
      throw;
    }
    break;
  case TextureData::Format::RGBA:  
    if(metadata.format == TextureMetadata::Format::RGBA || metadata.format == TextureMetadata::Format::sRGBA) {
      format = GL_RGBA; 
    } else {
      throw;
    }
    break;
  case TextureData::Format::RED:  
    if(metadata.format == TextureMetadata::Format::RED) {
      format = GL_RED; 
    } else {
      throw;
    }
    break;
  }
  

  console::info("Updating texture data (ID " + std::to_string(ID) + ")");
  glTextureSubImage2D(ID, 0, offsetX, offsetY, data.width, data.height, format, GL_UNSIGNED_BYTE, data.data.get());


};

void Texture2D::bindToUnit(unsigned int unit){
  glBindTextureUnit(unit, ID);
}

std::string Texture2D::toString() const {
  std::string str = "2D Texture (ID: " + std::to_string(ID) + ")\nMetadata: {\n" + metadata.toString() + "}";
  return str;
}

TextureData loadImageData(std::filesystem::path file, bool flip) {
  stbi_set_flip_vertically_on_load(flip);
  TextureData td;

  struct D {
    void operator()(unsigned char* p) const
    {
      console::warning("Deleting texture data");
    }
  };
  int width, height, nrChannels;
  td.data = std::shared_ptr<unsigned char>(stbi_load(file.string().c_str(), &width, &height, &nrChannels, 0), D());
  td.width = width;
  td.height = height;
  switch(nrChannels) {
  case 1:
    td.format = TextureData::Format::RED;
    break;
  case 3:
    td.format = TextureData::Format::RGB;
    break;
  case 4:
    td.format = TextureData::Format::RGBA;
    break;
  }
  console::info("Loaded texture at path " + file.string());
  return td; 
}

