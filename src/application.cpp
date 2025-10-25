#include "application.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "shader.hpp"
#include "cubes.hpp"
#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "orbit.hpp"



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app) return;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app) return;
    app->camera.handleMouseMovement(xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

Application::Application(int widht, int height, const char *title) {
  init(widht, height, title);
}

void Application::init(int width, int height, const char *title) {

  if (!glfwInit()) {
    std::cerr << "Error Initializing glfw\n";
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Make Window
  m_window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (m_window == NULL) {
    std::cerr << "Error making window\n";
  }

  // The current context will be window
  glfwMakeContextCurrent(m_window);

  // Load glad to get all the opengl thingy
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Error Initializing glad \n";
  }
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
   glfwSetWindowUserPointer(m_window, this); 
    glfwSetCursorPosCallback(m_window, mouse_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    

  glEnable(GL_DEPTH_TEST);
}

void Application::render() {
    Shader basicShader("shader/vertex.glsl", "shader/fragment.glsl");


		// Center stationary
    Cube center(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    center.animation(0.0f, 0.0f, false);

		// Moving one's
    Cube cube1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    Cube cube2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    Cube cube3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    
    cube1.animation(2.5f, 0.7f, true);  
    cube2.animation(4.0f, 0.5f, true);   
    cube3.animation(5.5f, 0.3f, true);   


		// Create orbits
    OrbitPath orbit1(2.5f, 200);
    OrbitPath orbit2(4.0f, 200);
    OrbitPath orbit3(5.5f, 200);
    
    while (!glfwWindowShouldClose(m_window)) {
        glClearColor(0.08f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.processCamera(m_window);
        camera.updateCamera(m_window);
        
        basicShader.use();
        basicShader.setMat4("projection", camera.getProjectionMatrix());
        basicShader.setMat4("view", camera.getViewMatrix());
        
// Identity matrix for orbit path
				glm::mat4 identityMatrix = glm::mat4(1.0f);
        basicShader.setMat4("model", identityMatrix);
        
        orbit1.Draw();
        orbit2.Draw();
        orbit3.Draw();
        
        basicShader.setMat4("model", center.getModelMatrix());
        center.Draw();
        
        basicShader.setMat4("model", cube1.getModelMatrix());
        cube1.Draw();
        
        basicShader.setMat4("model", cube2.getModelMatrix());
        cube2.Draw();
        
        basicShader.setMat4("model", cube3.getModelMatrix());
        cube3.Draw();
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}
