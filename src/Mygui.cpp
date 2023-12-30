#include "Mygui.h"
#include "Camera.h"

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

void Mygui::update(Camera cam, SHADERINPUT& shape)
{

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

  ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("carmera pos x : %f y : %f z : %f", cam._cameraPos.x, cam._cameraPos.y, cam._cameraPos.z);

  if (ImGui::Button("Circle Shader"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      shape = SHADERINPUT::CIRCLE;
  if (ImGui::Button("Qurd Shader"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      shape = SHADERINPUT::QURD;
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