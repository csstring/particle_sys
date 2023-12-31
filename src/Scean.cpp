#include "Scean.h"
#include "GLM/ext.hpp"
#include "Camera.h"
#include "PerlinNoise.h"
#include "Particle.h"
//0 1000
void Scean::initialize()
{
  _particleManager.initialize();
  _CVManager.initialize(_particleManager.posID, _particleManager.getParticleCount());
}

void Scean::update(const Camera& camera, float dt)
{
  glm::vec4 gravity = camera.getWorldXYPosition();
  // gravity.z /= 3;
  // std::cout << "x : " << camera._lastX << " y : " << camera._lastY << std::endl;
  // gravity.z += 0.2;
  // gravity.x = 0; gravity.y = 0;gravity.z = -8;
  // std::cout << glm::to_string(gravity) << std::endl;
  _CVManager.update(dt, gravity);
}

void Scean::draw()
{
  _particleManager.draw();
}