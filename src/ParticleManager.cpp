#include "ParticleManager.h"
#include "GL/glew.h"
#include "Camera.h"
#include "Particle.h"
#include <numeric>
#include <random>

ParticleManager::~ParticleManager()
{
  glDeleteVertexArrays(1, &_VAO);
  glDeleteBuffers(1, &posID);
}
// uint32 _VAO, velID, posID, colorID ,lifeID,radID ;
void ParticleManager::initialize()
{
  _particles.resize(_particleCount);
  const std::vector<glm::vec4> rainbow = {
        {1.0f, 0.0f, 0.0f, 1.0f},  // Red
        {1.0f, 0.65f, 0.0f, 1.0f}, // Orange
        {1.0f, 1.0f, 0.0f, 1.0f},  // Yellow
        {0.0f, 1.0f, 0.0f, 1.0f},  // Green
        {0.0f, 0.0f, 1.0f, 1.0f},  // Blue
        {0.3f, 0.0f, 0.5f, 1.0f},  // Indigo
        {0.5f, 0.0f, 1.0f, 1.0f}   // Violet/Purple
  };

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dp(-1.0f, 1.0f);
  std::uniform_int_distribution<size_t> dc(0, rainbow.size() - 1);
  std::uniform_real_distribution<float> randomTheta(-3.141592f, 3.141592f);
  std::uniform_real_distribution<float> randomSpeed(-2.0f, 2.0f);
  std::uniform_real_distribution<float> randomLife(0.0f, 1.0f);

  for (auto& p : _particles){
    const float theta = dp(gen);
    const float theta2 = dp(gen);
    p._position = glm::vec4(theta, theta2, 0.0, 1.0);
    // p._velocity = glm::vec4(randomSpeed(gen), randomSpeed(gen), randomSpeed(gen),0);
    p._velocity = glm::vec4(0.0f);
    p._color = rainbow[dc(gen)];
    // p._radius = (dp(gen) + 1.3f) * 1.02f;
    // p._life = 1.0f;
  }

  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);
  glGenBuffers(1, &posID);
  glBindBuffer(GL_ARRAY_BUFFER, posID);
  glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(Particle), _particles.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _position));
  glEnableVertexAttribArray(0);

  // Velocity
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _velocity));
  glEnableVertexAttribArray(1);

  // Color
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _color));
  glEnableVertexAttribArray(2);

  // // Life
  // glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _life));
  // glEnableVertexAttribArray(3);

  // // Radius
  // glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, _radius));
  // glEnableVertexAttribArray(4);

  glBindVertexArray(0);
}

void ParticleManager::update(float dt)
{ 
  // dt *= 0.005;
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

void ParticleManager::draw()
{
  glBindVertexArray(_VAO);
  glDrawArrays(GL_POINTS, 0, _particleCount);
  glBindVertexArray(0);
}
