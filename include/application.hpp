#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "camera.hpp"


class Application {
public:
		Application(int width, int height, const char* title);
		void init(int width, int height, const char* title);
  void render();
  void processInput();
  void cleanUp();
 Camera camera; 


private:
		GLFWwindow *m_window;
};

#endif
