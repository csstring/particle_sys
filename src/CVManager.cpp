#include "CVManager.h"
#include <fstream>
#include <sstream>
#include <OpenGL/OpenGL.h>

void CVManager::initialize(uint32 VBO, uint64 count)
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
  clVBO = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, VBO, &ret);
  if (ret != 0){
    std::cout << ret << std::endl;
    ft_assert("clCreateFromGLBuffer");
  }
  debug1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            count * sizeof(float), NULL, &ret);
  debug2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            count * sizeof(float), NULL, &ret);
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
  C = (float*)malloc(sizeof(float)*count);
  D = (float*)malloc(sizeof(float)*count);
  global_item_size = count;
  local_item_size = 64;
}

void CVManager::update(float dt, const glm::vec4& gravity)
{
    static size_t quarterIndex = 0;
    const size_t totalParticles = global_item_size;  // Total number of particles
    const size_t quarterSize = totalParticles / 4;  // Size of each quarter
    dt *= 0.4;

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &clVBO);
    clSetKernelArg(kernel, 1, sizeof(float), &dt);
    clSetKernelArg(kernel, 2, 4 * sizeof(float), &gravity);
    ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), &debug1);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), &debug2);
    clEnqueueAcquireGLObjects(command_queue, 1, &clVBO, 0, nullptr, nullptr);

    // Calculate the starting point for this update
    // size_t global_work_offset = quarterIndex * quarterSize;

    // Update only a quarter of the particles
    clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr, &global_item_size, &local_item_size, 0, nullptr, nullptr);
    clEnqueueReleaseGLObjects(command_queue, 1, &clVBO, 0, nullptr, nullptr);
    clFinish(command_queue);

    // ret = clEnqueueReadBuffer(command_queue, debug1, CL_TRUE, 0, 
    //         totalParticles * sizeof(float), C, 0, NULL, NULL);
    // ret = clEnqueueReadBuffer(command_queue, debug2, CL_TRUE, 0, 
    //         totalParticles * sizeof(float), D, 0, NULL, NULL);
    // for (int i =0; i < totalParticles; ++i){
    //   std::cout << "c : "<<C[i] << "  D : " << D[i] << " dt : " << dt << std::endl;
    // }
    // Move to the next quarter for the next update
    quarterIndex = (quarterIndex + 1) % 4;
}

CVManager::~CVManager()
{
  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(clVBO);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
}