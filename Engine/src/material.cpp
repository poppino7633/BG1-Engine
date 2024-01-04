#include "includes.h"
#include "include/material.h"

void BFMaterial::bind(){
  if(diffuse) diffuse->bindToUnit(0);
  if(specular) specular->bindToUnit(1);
  if(normal) normal->bindToUnit(2);
}
