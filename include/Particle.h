#pragma once
#include "Common.h"
struct alignas(16) Particle
{
  glm::vec4 _position;
  glm::vec4 _velocity;
  glm::vec4 _color;
  // float _life = 0.0f;
  // float p4 = 0.0f;
  // float _radius = 1.0f;
  // float p5 = 0.0f;
};
