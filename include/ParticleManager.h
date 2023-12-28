#pragma once
#include "Common.h"
#include "PerlinNoise.h"

//thread
struct Particle;
class Camera;
class ParticleManager : Noncopyable
{
  private:
    std::vector<Particle> _particles[MAXBUFFERSIZE];
    uint32 _particleCount;

  public:
    uint32 _VAO;
    glm::vec3 _camPos;
    uint32 posID[MAXBUFFERSIZE];

  public:
    ParticleManager(uint32 count) : _particleCount(count / MAXBUFFERSIZE){};
    ~ParticleManager();//delete data

    void initialize();
    void update(float dt);
    void draw();
    uint32 getParticleCount(){return _particleCount;};
};