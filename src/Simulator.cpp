#include "Simulator.h"
#include "Scean.h"
#include "Camera.h"

Simulator::~Simulator(){}

void Simulator::initialize(uint32 particlecount)
{
  this->_scean = std::make_unique<Scean>(particlecount);
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