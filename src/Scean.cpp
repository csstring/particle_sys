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

void Scean::update(const Camera& camera, float dt, int32 drawCount)
{
  glm::vec4 gravity = camera.getWorldCursorPos();
  if (_isGravityOn == false)
    gravity.w = 0;
  _CVManager.update(dt, gravity, drawCount);
}

void Scean::draw(uint32 drawCount)
{
  _particleManager.draw(drawCount);
}