#pragma once
#include <OpenCL/opencl.h>
#include "Common.h"
#include "KernelProgram.h"
#include <unordered_map>
class CVManager
{
  private:
    cl_platform_id platform_id;
    cl_device_id device_id;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
    cl_command_queue command_queue;
    cl_mem clVBO;
    cl_mem debug1, debug2, debug3;
    uint64 global_item_size = 1024;
    uint64 local_item_size = 64;
    std::vector<KernelProgram> _programs;
    float* C;
    float* D;
    float* F;

  public:

    cl_context context;
    CVManager(){};
    ~CVManager();
    void initialize(uint32 VBO, uint64 count);
    void update(float dt, const glm::vec4& gravity, int32 drawCount);
};
