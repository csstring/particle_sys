#include "CVManager.h"
#include <fstream>
#include <sstream>
#include <OpenGL/OpenGL.h>

void CVManager::initialize(uint32 VBO[MAXBUFFERSIZE], uint64 count)
{
  std::ifstream sourceCodeStream("./kernelSource/particle_sys.cl", std::ios::in);
  std::string kernerCode;
  
  if (sourceCodeStream.is_open())
  {
    std::stringstream ss;
    ss << sourceCodeStream.rdbuf();
    kernerCode = ss.str();
    sourceCodeStream.close();
  }
  else
    ft_assert("kernel code open fail");

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
    CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)shareGroup,
    0 // Terminate the list
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
  for (int i =0; i < MAXBUFFERSIZE; ++i)
    clVBO[i] = clCreateFromGLBuffer(context, CL_MEM_WRITE_ONLY, VBO[i], &ret);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clCreateFromGLBuffer");
  }
  const char* code = kernerCode.c_str();
  size_t tmplength = kernerCode.size();
  program = clCreateProgramWithSource(context, 1, &code, &tmplength, &ret);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clCreateProgramWithSource");
  }
  ret = clBuildProgram(program, 1, &device_id, nullptr, nullptr, nullptr);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clBuildProgram");
  }
  kernel = clCreateKernel(program, "particle_sys", &ret);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clCreateKernel");
  }

  global_item_size = count / MAXBUFFERSIZE;
  local_item_size = 64;
}

void CVManager::update(float dt, uint32 curBufferIdx)
{
    dt *= 0.0005;

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &clVBO[curBufferIdx]);
    clSetKernelArg(kernel, 1, sizeof(float), &dt);

    clEnqueueAcquireGLObjects(command_queue, 1, &clVBO[curBufferIdx], 0, nullptr, nullptr);
    clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr, &global_item_size, &local_item_size, 0, nullptr, nullptr);

    clEnqueueReleaseGLObjects(command_queue, 1, &clVBO[curBufferIdx], 0, nullptr, nullptr);
    clFinish(command_queue);

}

CVManager::~CVManager()
{
  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  for (int i =0; i < MAXBUFFERSIZE; ++i)
    ret = clReleaseMemObject(clVBO[i]);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
}