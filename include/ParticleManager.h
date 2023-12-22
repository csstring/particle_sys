#pragma once
#include "Common.h"
#include "PerlinNoise.h"

//thread
struct Particle;
class Camera;
class ParticleManager : Noncopyable
{
  private:
    std::vector<Particle> _particles;
    uint32 _particleCount;
    uint32 _VAO, velID, posID, colorID ,lifeID,radID ;

  public:
    glm::vec3 _camPos;

  public:
    ParticleManager(uint32 count) : _particleCount(count){};
    ~ParticleManager();//delete data

    void initialize();
    void update(const Camera& camera);
    void draw();

};