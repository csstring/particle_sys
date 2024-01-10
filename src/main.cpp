#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include "Window.h"
#include "shader.h"
#include "Simulator.h"
#include "Camera.h"
#include <iostream>
#include "Mygui.h"
#include <OpenCL/opencl.h>
#include "ShaderManager.h"

Camera      _camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    (void)window;
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(xposIn, yposIn);
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (_camera._isFirst)
    {
        _camera._lastX = xpos;
        _camera._lastY = ypos;
        _camera._isFirst = false;
    }

    float xoffset = xpos - _camera._lastX;
    float yoffset = _camera._lastY - ypos;

    _camera._lastX = xpos;
    _camera._lastY = ypos;

    if (_camera._isOn == false)
        return ;
    _camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void leakCheck()
{
    system("leaks particle");
}

int main(int ac, char** av) 
{
    // atexit(leakCheck);
    if (ac < 2){
        std::cerr << "input error : particle max count missing\n";
        return 1;
    } else if (ac > 2) {
        std::cerr << "input error : to many argument\n";
        return 1;
    }
    float count = std::atof(av[1]);
    if (count == 0.0f){
        std::cerr << "input error : not number";
        return 1;
    }

    ShaderManager shaderManager;
    SHADERINPUT shaderInput = SHADERINPUT::QURD;
    Mygui       mygui;
    Window      window;
    Simulator*  simulator = new Simulator();
    
    window.initialize();
    _camera.initialize();
    shaderManager.initialize();
    mygui.initialize(window._window);
    simulator->initialize(std::ceil(count / 64.0f) * 64.0f);

    glfwSetFramebufferSizeCallback(window._window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window._window, mouse_callback);
    glfwSetInputMode(window._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glm::mat4 projection = glm::perspective(glm::radians(_camera._fov), ASPECT_RATIO, _camera._zNear, _camera._zFar);
    constexpr float delta = 1.0f / 60.0f;

    while (window.isWindowClose() == false)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mygui.update(_camera, shaderInput, *simulator);
        window.processInput(delta , _camera, *simulator);
        _camera.update();
        glPointSize(simulator->_pointSize);
        shaderManager.use(shaderInput);
        shaderManager.setMat4("projection", projection);
        shaderManager.setMat4("view", _camera._view);
        shaderManager.setVec4("cursorPos", projection * _camera._view * _camera.getWorldCursorPos());
        simulator->update(delta * simulator->_speed, _camera);
        simulator->draw();
        mygui.render();
        window.bufferSwap();
        glfwPollEvents();
    }
    delete simulator;
    glfwDestroyWindow(window._window);
    glfwTerminate();
}