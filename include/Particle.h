#pragma once
#include "Common.h"
struct alignas(16) Particle
{
  glm::vec3 _position;
  float p1 = 0.0f;
  glm::vec3 _velocity;
  float p2 = 0.0f;
  glm::vec3 _color;
  float p3 = 0.0f;
  // float _life = 0.0f;
  // float p4 = 0.0f;
  // float _radius = 1.0f;
  // float p5 = 0.0f;
};
