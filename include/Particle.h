#pragma once
#include "Common.h"
struct Particle
{
  glm::vec3 _position;
  glm::vec3 _velocity;
  glm::vec3 _color;
  float     _life = 0.0f;
  float     _radius = 1.0f;
};
