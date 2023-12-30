#pragma once
#include <OpenCL/opencl.h>
#include "Common.h"

class CVManager
{
  private:
    cl_platform_id platform_id;
    cl_device_id device_id;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
    cl_context context;
    cl_command_queue command_queue;
    cl_mem clVBO;
    cl_mem debug1, debug2;
    cl_program program;
    cl_kernel kernel;
    uint64 global_item_size = 1024;
    uint64 local_item_size = 64;
    float* C;
    float* D;
  public:
    CVManager(){};
    ~CVManager();
    void initialize(uint32 VBO, uint64 count);
    void update(float dt, const glm::vec4& gravity);
};
