#pragma once

#include "Common.h"

struct GLFWwindow;
class Camera;
class Mygui
{
  private:
    /* data */
  public:
    void initialize(GLFWwindow* window);
    void update(Camera cam);
    void render(void);
    Mygui(){};
    ~Mygui();
};

