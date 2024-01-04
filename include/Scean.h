#pragma once
#include "Common.h"
#include <map>
#include <utility>
#include "ParticleManager.h"
#include "CVManager.h"

class Camera;
class Scean : Noncopyable
{
  private:

  public:
    ParticleManager _particleManager;
    CVManager _CVManager;
    bool _isGravityOn = false;
    bool _isGeneratorOn = false;
      
  public:
    Scean() = delete;
    Scean(uint32 particleCount)
    : _particleManager(particleCount){
    };
    ~Scean(){};

    void initialize();

    void update(const Camera& camera, float dt, int32 drawCount);
    void draw(uint32 drawCount);
};
