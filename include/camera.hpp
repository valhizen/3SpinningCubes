#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"

class Camera{
public:
		Camera();
		void init();

		void processCamera(GLFWwindow *window);
		void updateCamera(GLFWwindow *window);


		glm::mat4 getViewMatrix() const {return view;}
		glm::mat4 getProjectionMatrix() const {return projection;}

    void handleMouseMovement(double xpos, double ypos);
    void handleMouseScroll(double yoffset);
    float getFOV() const { return fov; }

    // glm::vec3 position;
    // glm::vec3 rotation;
    // glm::vec3 scale;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;

		glm::mat4 view;
		glm::mat4 projection;

    float fov;
    float yaw;
    float pitch;
    bool firstMouse;
    double lastX;
    double lastY;


};

#endif
