#include "ParticleManager.h"
#include "GL/glew.h"
#include "Camera.h"
#include "Particle.h"
#include <numeric>
#include <random>

ParticleManager::~ParticleManager()
{
  glDeleteVertexArrays(1, &_VAO);
  for (int i =0; i < MAXBUFFERSIZE; ++i)
    glDeleteBuffers(1, &posID[i]);
}
// uint32 _VAO, velID, posID, colorID ,lifeID,radID ;
void ParticleManager::initialize()
{
  for (int i =0; i < MAXBUFFERSIZE; ++i)
    _particles[i].resize(_particleCount);
  const std::vector<glm::vec3> rainbow = {
        {1.0f, 0.0f, 0.0f},  // Red
        {1.0f, 0.65f, 0.0f}, // Orange
        {1.0f, 1.0f, 0.0f},  // Yellow
        {0.0f, 1.0f, 0.0f},  // Green
        {0.0f, 0.0f, 1.0f},  // Blue
        {0.3f, 0.0f, 0.5f},  // Indigo
        {0.5f, 0.0f, 1.0f}   // Violet/Purple
  };

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dp(-1.0f, 1.0f);
  std::uniform_int_distribution<size_t> dc(0, rainbow.size() - 1);
  std::uniform_real_distribution<float> randomTheta(-3.141592f, 3.141592f);
  std::uniform_real_distribution<float> randomSpeed(-2.0f, 2.0f);
  std::uniform_real_distribution<float> randomLife(0.0f, 1.0f);

  for (int i =0; i < MAXBUFFERSIZE; ++i){
    for (auto& p : _particles[i]){
      const float theta = randomTheta(gen);
      p._position = glm::vec3(cos(theta), -sin(theta), 0.0) * randomLife(gen) * 0.1f +
                      glm::vec3(0.0f, -0.3f, 0.0f);
      p._velocity = glm::vec3(randomSpeed(gen), randomSpeed(gen), randomSpeed(gen));
      p._color = rainbow[dc(gen)];
    }
  }

  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);
  glGenBuffers(MAXBUFFERSIZE, posID);
  for (int i =0; i < MAXBUFFERSIZE; ++i)
  {
    glBindBuffer(GL_ARRAY_BUFFER, posID[i]);
    glBufferData(GL_ARRAY_BUFFER, _particles[i].size() * sizeof(Particle), _particles[i].data(), GL_DYNAMIC_DRAW);
  }
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _position));
    glEnableVertexAttribArray(0);

    // Velocity
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _velocity));
    glEnableVertexAttribArray(1);

    // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _color));
    glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void ParticleManager::draw()
{
  glBindVertexArray(_VAO);
  for (int i =0; i < MAXBUFFERSIZE; ++i){
    glBindBuffer(GL_ARRAY_BUFFER, posID[i]);
    glDrawArrays(GL_POINTS, 0, _particleCount);
  }
  glBindVertexArray(0);
}

void ParticleManager::update(float dt)
{ 
  // std::random_device rd;
  // std::mt19937 gen(rd());
  // std::uniform_real_distribution<float> randomTheta(-3.141592f, 3.141592f);
  // std::uniform_real_distribution<float> randomSpeed(1.5f, 2.0f);
  // std::uniform_real_distribution<float> randomLife(0.0f, 1.0f);

  // int newCount = 5000;
  // for (auto& p : _particles)
  // {
  //   if (p._life < 0.0f && newCount > 0)
  //   {
  //     const float theta = randomTheta(gen);
  //     p._position = glm::vec3(cos(theta), -sin(theta), 0.0) * randomLife(gen) * 0.1f +
  //                   glm::vec3(0.0f, -0.3f, 0.0f);
  //     p._velocity = glm::vec3(-1.0f, 0.0f,0.0f) * randomSpeed(gen);
  //     p._life = randomLife(gen) * 1.5;
  //     newCount--;
  //   }
  // }
  
  // constexpr float cordi = 0.5f;
  // constexpr float groundHeight = -1.0f;
  // constexpr glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);

  // for (auto& p : _particles)
  // {
  //   if (p._life < 0.0f) 
  //     continue;
  //   p._velocity = p._velocity + gravity *dt;
  //   p._position += p._velocity* dt;
  //   p._life -= dt;
  // }
}

