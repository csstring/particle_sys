#include "CVManager.h"
#include <fstream>
#include <sstream>
#include <OpenGL/OpenGL.h>
#include <random>

void CVManager::initialize(uint32 VBO, uint64 count)
{
  ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  if (ret != CL_SUCCESS) {
      std::cout << "Error getting platform ID: " << ret << std::endl;
      ft_assert("clGetPlatformIDs");
  }

  // Get device IDs
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
  if (ret != CL_SUCCESS || ret_num_devices == 0) {
      std::cout << "Error getting device IDs or no devices found: " << ret << std::endl;
      ft_assert("clGetDeviceIDs");
  }

  // Verify GL context and share group
  CGLContextObj glContext = CGLGetCurrentContext();
  if (glContext == NULL) {
      ft_assert("CGLGetCurrentContext returned NULL");
  }
  CGLShareGroupObj shareGroup = CGLGetShareGroup(glContext);
  if (shareGroup == NULL) {
      ft_assert("CGLGetShareGroup returned NULL");
  }
  cl_context_properties properties[] = {
    CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)shareGroup,0
  };

  context = clCreateContext(properties, 1, &device_id, nullptr, nullptr, &ret);
  if (ret != CL_SUCCESS) {
      std::cout << "Error creating context: " << ret << std::endl;
      ft_assert("clCreateContext");
  }

  command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clCreateCommandQueue");
  }
  clVBO = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, VBO, &ret);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clCreateFromGLBuffer");
  }
  debug1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            count * sizeof(float), NULL, &ret);
  debug2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            count * sizeof(float), NULL, &ret);
  debug3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            count * sizeof(float), NULL, &ret);

  _programs.resize(4);
  _programs[MAIN_ROOP].initialize(context, device_id, "./kernelSource/particle_sys.cl", "particle_sys");
  _programs[INIT_CIRCLE].initialize(context, device_id, "./kernelSource/init_circle.cl", "init_circle");
  _programs[INIT_PLANE].initialize(context, device_id, "./kernelSource/init_plane.cl", "init_plane");
  _programs[GENERATOR].initialize(context, device_id, "./kernelSource/particle_generator.cl", "particle_generator");

  C = (float*)malloc(sizeof(float)*count);
  D = (float*)malloc(sizeof(float)*count);
  F = (float*)malloc(sizeof(float)*count);
  global_item_size = count;
  local_item_size = 64;
}

void CVManager::initCircle()
{
  cl_kernel kernel = _programs[INIT_CIRCLE]._kernel;
  uint32 seed = _rd();

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &clVBO);
  clSetKernelArg(kernel, 1, sizeof(uint32), &seed);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &debug1);
  clSetKernelArg(kernel, 3, sizeof(cl_mem), &debug2);
  clSetKernelArg(kernel, 4, sizeof(cl_mem), &debug3);
  clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr, &global_item_size, nullptr, 0, nullptr, nullptr);
  clFinish(command_queue);
}

void CVManager::initPlane()
{
  cl_kernel kernel = _programs[INIT_PLANE]._kernel;
  uint32 seed = _rd();

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &clVBO);
  clSetKernelArg(kernel, 1, sizeof(uint32), &seed);
  clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr, &global_item_size, nullptr, 0, nullptr, nullptr);
  clFinish(command_queue);
}
void CVManager::initBlackHole()
{}

void CVManager::update(float dt, const glm::vec4& gravity, int32 drawCount)
{
    static size_t quarterIndex = 0;
    const size_t totalParticles = drawCount;  // Total number of particles
    const size_t quarterSize = totalParticles / 4;  // Size of each quarter
    const size_t geCount = 5000;
    dt *= 0.4;
    cl_kernel kernel = _programs[MAIN_ROOP]._kernel;
    cl_kernel generator = _programs[GENERATOR]._kernel;
    uint32 seed = _rd();
    clSetKernelArg(generator, 0, sizeof(cl_mem), &clVBO);
    clSetKernelArg(generator, 1, sizeof(uint32), &seed);
    clSetKernelArg(generator, 2, 4 * sizeof(float), &gravity);
    clSetKernelArg(generator, 3, sizeof(float), &dt);
    clEnqueueNDRangeKernel(command_queue, generator, 1, nullptr, &geCount, nullptr, 0, nullptr, nullptr);
    clFinish(command_queue);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &clVBO);
    clSetKernelArg(kernel, 1, sizeof(float), &dt);
    clSetKernelArg(kernel, 2, 4 * sizeof(float), &gravity);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &debug1);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), &debug2);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), &debug3);
    // clEnqueueAcquireGLObjects(command_queue, 1, &clVBO, 0, nullptr, nullptr);
    clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr, &totalParticles, nullptr, 0, nullptr, nullptr);
    // clEnqueueReleaseGLObjects(command_queue, 1, &clVBO, 0, nullptr, nullptr);
    clFinish(command_queue);
    // ret = clEnqueueReadBuffer(command_queue, debug1, CL_TRUE, 0, 
    //         geCount * sizeof(float), C, 0, NULL, NULL);
    // ret = clEnqueueReadBuffer(command_queue, debug2, CL_TRUE, 0, 
    //         geCount * sizeof(float), D, 0, NULL, NULL);
    // ret = clEnqueueReadBuffer(command_queue, debug3, CL_TRUE, 0, 
    //         geCount * sizeof(float), F, 0, NULL, NULL);
    // clFinish(command_queue);
    // for (int i =0; i < geCount; ++i){
    //   std::cout << "life : "<<C[i] << "  x : " << D[i] << " y : " << F[i] << std::endl;
    // }
    // std::cout << glm::to_string(gravity) << std::endl;
}

CVManager::~CVManager()
{
  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseMemObject(clVBO);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
}