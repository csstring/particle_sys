#include "Simulator.h"
#include "GL/glew.h"
#include <random>
#include <algorithm>
#include "shader.h"
#include <unistd.h>
#include "Scean.h"
#include "GLM/ext.hpp"
#include "GLM/gtx/string_cast.hpp"
#include "Scean.h"
#include "Camera.h"
#include "Particle.h"

Simulator::~Simulator()
{
  if (_scean != nullptr)
    delete _scean;
}

void Simulator::initialize(uint32 particlecount)
{
  this->_scean = new Scean(particlecount);
  this->_scean->initialize();
  _totalCount = particlecount;
  _drawCount = _totalCount;
}

void Simulator::draw(void)
{
  _scean->draw(_drawCount);
}

void Simulator::update(float delta, const Camera& camera)
{
  _scean->update(camera, delta, _drawCount);
}