#include "Mygui.h"
#include "Camera.h"
#include "Simulator.h"
#include "Scean.h"

void Mygui::initialize(GLFWwindow* window)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

void Mygui::update(Camera cam, SHADERINPUT& shape, Simulator& simul)
{

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Mandatory");                          // Create a window called "Hello, world!" and append into it.

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("carmera pos x : %f y : %f z : %f", cam._cameraPos.x, cam._cameraPos.y, cam._cameraPos.z);

  if (ImGui::Button("Circle Shader"))                           
      shape = SHADERINPUT::CIRCLE;
  if (ImGui::Button("Qurd Shader"))
      shape = SHADERINPUT::QURD;
  
  ImGui::SliderInt("Particle Count", &simul._drawCount, 0, simul._totalCount);
  ImGui::End();

  ImGui::Begin("Bonus"); // Start the Bonus window

  ImGui::SliderInt("Particle Size", &simul._pointSize, 1, 10);
  ImGui::SliderInt("Simul Speed", &simul._speed, 0, 5);
  ImGui::Checkbox("Enable Generator", &simul._scean->_isGeneratorOn);

  // if (ImGui::Button("init Plane scene"))                           
  //     simul._scean->_CVManager.initPlane();
  // if (ImGui::Button("init circle scene"))
  //     simul._scean->_CVManager.initCircle();

  ImGui::End();
}

void Mygui::render(void)
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Mygui::~Mygui()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}