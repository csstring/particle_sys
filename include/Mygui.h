#pragma once

#include "Common.h"
#include "EnumHeader.h"
struct GLFWwindow;
class Simulator;
class Camera;
class Mygui
{
  private:
    /* data */
  public:
    void initialize(GLFWwindow* window);
    void update(Camera cam, SHADERINPUT& shape, Simulator& simul);
    void render(void);
    Mygui(){};
    ~Mygui();
};

