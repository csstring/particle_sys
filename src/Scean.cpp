#include "Scean.h"
#include "GLM/ext.hpp"
#include "Camera.h"
#include "PerlinNoise.h"
#include "Particle.h"
//0 1000
void Scean::initialize()
{
  _particleManager.initialize();
}

void Scean::update(const Camera& camera)
{
  _particleManager.update(camera);
}

void Scean::draw()
{
  _particleManager.draw();
}