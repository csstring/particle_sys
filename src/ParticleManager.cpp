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
  glDeleteBuffers(1, &velID);
  glDeleteBuffers(1, &colorID);
  glDeleteBuffers(1, &lifeID);
  glDeleteBuffers(1, &radID);
}
// uint32 _VAO, velID, posID, colorID ,lifeID,radID ;
void ParticleManager::initialize()
{

  _particles.resize(_particleCount);

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

  for (auto& p : _particles){
    p._position = glm::vec3(dp(gen), dp(gen), 1.0f);
    p._color = rainbow[dc(gen)];
    p._radius = (dp(gen) + 1.3f) * 0.02f;
    p._life = -1.0f;
    std::cout << glm::to_string(p._position) << ' '<< glm::to_string(p._color) << "\n";
  }


  {
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &posID);
    glBindBuffer(GL_ARRAY_BUFFER, posID);
    glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &velID);
    glBindBuffer(GL_ARRAY_BUFFER, velID);
    glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &colorID);
    glBindBuffer(GL_ARRAY_BUFFER, colorID);
    glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &lifeID);
    glBindBuffer(GL_ARRAY_BUFFER, lifeID);
    glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &radID);
    glBindBuffer(GL_ARRAY_BUFFER, radID);
    glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);
  }
}

void ParticleManager::update(const Camera& camera)
{

    {
      glBindVertexArray(_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, posID);
      glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(glm::vec3), &(_particles.data()->_position));

      glBindBuffer(GL_ARRAY_BUFFER, velID);
      glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(glm::vec3), &(_particles.data()->_velocity));

      glBindBuffer(GL_ARRAY_BUFFER, colorID);
      glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(glm::vec3), &(_particles.data()->_color));

      glBindBuffer(GL_ARRAY_BUFFER, lifeID);
      glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(float), &(_particles.data()->_life));

      glBindBuffer(GL_ARRAY_BUFFER, radID);
      glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(float), &(_particles.data()->_radius));

      glBindVertexArray(0);
    }
}

void ParticleManager::draw()
{
  glBindVertexArray(_VAO);
  glDrawArrays(GL_POINTS, 0, _particleCount);
  glBindVertexArray(0);

}
