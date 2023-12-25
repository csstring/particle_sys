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
  _CVManager.update(dt);
}

void Scean::draw()
{
  _particleManager.draw();
}