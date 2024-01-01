#pragma once
#include "Common.h"
#include "PerlinNoise.h"
#include "Particle.h"
//thread
class Camera;
class ParticleManager : Noncopyable
{
  private:
    std::vector<Particle> _particles;
    uint32 _particleCount;
    uint32 _VAO;

  public:
    glm::vec3 _camPos;
    uint32 posID;

  public:
    ParticleManager(uint32 count) : _particleCount(count){};
    ~ParticleManager();//delete data

    void initialize();
    void update(float dt);
    void draw(uint32 drawCount);
    uint32 getParticleCount(){return _particleCount;};
};