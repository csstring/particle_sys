#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include "Window.h"
#include "shader.h"
#include "Simulator.h"
#include "Camera.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include "Mygui.h"
#include <OpenCL/opencl.h>
#include "ShaderManager.h"
Camera      _camera;
Mygui       mygui;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    _camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void cvcheck()
{
    cl_uint numPlatforms;
    clGetPlatformIDs(0, NULL, &numPlatforms);
    cl_platform_id* platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * numPlatforms);
    clGetPlatformIDs(numPlatforms, platforms, NULL);
    for (cl_uint i = 0; i < numPlatforms; ++i) {
    char info[1024];
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 1024, info, NULL);
    std::cout << "Platform Name: " << info << std::endl;

    clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 1024, info, NULL);
    std::cout << "Platform Vendor: " << info << std::endl;

    clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 1024, info, NULL);
    std::cout << "Platform Version: " << info << std::endl;

    clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 1024, info, NULL);
    std::cout << "Platform Extensions: " << info << std::endl;
    for (cl_uint i = 0; i < numPlatforms; ++i) {
    cl_uint numDevices;
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
    cl_device_id* devices = (cl_device_id*)malloc(sizeof(cl_device_id) * numDevices);
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);

    for (cl_uint j = 0; j < numDevices; ++j) {
        char info[1024];
        clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 1024, info, NULL);
        std::cout << "\tDevice Name: " << info << std::endl;

        size_t maxWorkGroupSize;
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(maxWorkGroupSize), &maxWorkGroupSize, NULL);
        std::cout << "\tMax Work Group Size: " << maxWorkGroupSize << std::endl;

    }
    free(devices);
    }
    if (strstr(info, "cl_khr_gl_sharing")) {
        std::cout << "\tSupports cl_khr_gl_sharing" << std::endl;
    }
    free(platforms);
    }
}

int main(int ac, char** av) 
{

    if (ac < 2){
        std::cerr << "input error : obj file path missing\n";
        return 1;
    } else if (ac > 2) {
        std::cerr << "input error : to many argument\n";
        return 1;
    }
    cvcheck();
    Window window;
    ShaderManager shaderManager;
    SHADERINPUT shaderInput = SHADERINPUT::CIRCLE;
    window.initialize();
    _camera.initialize();
    shaderManager.initialize();
    mygui.initialize(window._window);

    Simulator simulator;
    // simulator.initialize(std::atof(av[1]));
    simulator.initialize(std::ceil(std::atof(av[1]) / 64.0f) * 64.0f);
    std::cout << std::ceil(std::atof(av[1]) / 64.0f) * 64.0f << std::endl;
    // camera mouse call
    glfwSetFramebufferSizeCallback(window._window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window._window, mouse_callback);
    // glfwSetScrollCallback(window._window, scroll_callback);
    glfwSetInputMode(window._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glm::mat4 projection = glm::perspective(glm::radians(_camera._fov), ASPECT_RATIO, _camera._zNear, _camera._zFar);
    const float delta = 1.0f / 60.0f;
    while (window.isWindowClose() == false)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mygui.update(_camera, shaderInput, simulator);
        window.processInput(delta , _camera, simulator._scean);
        _camera.update();
        // std::cout << "x : " << _camera._lastX << " y : " << _camera._lastY << std::endl;
        shaderManager.use(shaderInput);
        shaderManager.setMat4("projection", projection);
        shaderManager.setMat4("view", _camera._view);
        shaderManager.setVec4("cursorPos", projection * _camera._view * _camera.getWorldCursorPos());
        simulator.update(delta, _camera);
        simulator.draw();
        mygui.render();
        window.bufferSwap();
        glfwPollEvents();
    }
    glfwTerminate();
}
