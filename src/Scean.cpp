#include "Scean.h"
#include "Camera.h"
#include "Particle.h"

void Scean::initialize()
{
  _particleManager.initialize();
  _CVManager.initialize(_particleManager._VBO, _particleManager.getParticleCount());
  // _CVManager.initCircle();
  _CVManager.initPlane();
}

void Scean::update(const Camera& camera, float dt, int32 drawCount)
{
  glm::vec4 gravity = camera.getWorldCursorPos();
  if (_isGravityOn == false)
    gravity.w = 0;
  if (_isGeneratorOn == true)
    _CVManager.particleGenerate(dt, gravity);
  _CVManager.update(dt, gravity, drawCount);
}

void Scean::draw(uint32 drawCount)
{
  _particleManager.draw(drawCount);
}