#include "texture.h"

class IMaterial {
public:
  virtual void bind() = 0;
};

class BFMaterial : public IMaterial {
public:
  std::shared_ptr<Texture2D> diffuse, specular, normal;
  BFMaterial(std::shared_ptr<Texture2D> diffuse,
             std::shared_ptr<Texture2D> specular,
             std::shared_ptr<Texture2D> normal)
      : diffuse(diffuse), specular(specular), normal(normal){}
  void bind();
};

class PBRMaterial : public IMaterial {
public:
  std::shared_ptr<Texture2D> albedo, metallic, roughness, normal, AO;
  void bind();
};
