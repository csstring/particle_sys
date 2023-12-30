#include "ShaderManager.h"
#include "shader.h"
#include "GL/glew.h"

void ShaderManager::initialize()
{
  circleShader = std::make_unique<Shader>();
  qurdShader = std::make_unique<Shader>();

  circleShader->initialize("./shaderSource/CircleVertexShader.glsl",
    "./shaderSource/CircleFragmentShader.glsl",
    "./shaderSource/CircleGeometryShader.glsl");
  qurdShader->initialize("./shaderSource/QurdVertexShader.glsl",
    "./shaderSource/QurdFragmentShader.glsl",
    "./shaderSource/QurdGeometryShader.glsl");
    
  _curProgramId = circleShader->_programId;
}

void ShaderManager::use(SHADERINPUT input)
{
	switch (input)
  {
    case SHADERINPUT::CIRCLE:
      circleShader->use();
      _curProgramId = circleShader->_programId;
      break;
    case SHADERINPUT::QURD:
      qurdShader->use();
      _curProgramId = qurdShader->_programId;
    default:
      break;
  }
}

void ShaderManager::setMat4(const std::string &name, glm::mat4 mat4) const
{
    glUniformMatrix4fv(glGetUniformLocation(_curProgramId, name.c_str()),1, false, &mat4[0].x);
}

void ShaderManager::setVec3(const std::string &name, glm::vec3 vec3) const
{
    glUniform3fv(glGetUniformLocation(_curProgramId, name.c_str()), 1, &vec3.x);
}

void ShaderManager::setUint(const std::string &name, unsigned int index) const
{
    glUniform1ui(glGetUniformLocation(_curProgramId, name.c_str()), index);
}

void ShaderManager::setFloat(const std::string &name, float index) const
{
    glUniform1f(glGetUniformLocation(_curProgramId, name.c_str()), index);
}
