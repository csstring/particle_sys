#include "Scean.h"
#include "GLM/ext.hpp"
#include "Camera.h"
#include "PerlinNoise.h"
#include "Particle.h"
//0 1000
void Scean::initialize()
{
  _particleManager.initialize();
  _CVManager.initialize(_particleManager.posID, _particleManager.getParticleCount(), _particleManager._VAO);
}

void Scean::update(const Camera& camera, float dt)
{
  static uint64 bufferCount = 0;
  _CVManager.update(dt, bufferCount);
  bufferCount = (bufferCount + 1) % MAXBUFFERSIZE;
}

void Scean::draw()
{
  _particleManager.draw();
}