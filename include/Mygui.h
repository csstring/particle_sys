#pragma once

#include "Common.h"
#include "EnumHeader.h"
struct GLFWwindow;
class Camera;
class Mygui
{
  private:
    /* data */
  public:
    void initialize(GLFWwindow* window);
    void update(Camera cam, SHADERINPUT& shape);
    void render(void);
    Mygui(){};
    ~Mygui();
};

