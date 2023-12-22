#pragma once
#include "Common.h"
#include <map>
#include <utility>
#include "ParticleManager.h"

class Camera;
class Scean : Noncopyable
{
  private:
    ParticleManager _particleManager;

  public:
    Scean() = delete;
    Scean(uint32 particleCount)
    : _particleManager(particleCount){
    };
    ~Scean(){};

    void initialize();

    void update(const Camera& camera);
    void draw();
};
