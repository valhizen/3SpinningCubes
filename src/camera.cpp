#include "camera.hpp"
#include "GLFW/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(){
		init();
}

void Camera::init(){
		// cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
cameraPos = glm::vec3(0.0f, 5.0f, 10.0f); 
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Initialize camera angles
    yaw = -90.0f;
    pitch = -30.0f;
    fov = 45.0f;
    
    // Initialize mouse tracking
    firstMouse = true;
    lastX = 0.0;
    lastY = 0.0;

		projection = glm::perspective(glm::radians(45.0f),800.0f / 600.0f, 0.1f,100.0f );
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::processCamera(GLFWwindow *window){
		const float cameraSpeed = 0.05f;
		if (glfwGetKey(window, GLFW_KEY_W)== GLFW_PRESS){
				cameraPos += cameraFront * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S)== GLFW_PRESS){
				cameraPos -= cameraFront * cameraSpeed;
		}
				if (glfwGetKey(window, GLFW_KEY_A)== GLFW_PRESS){
						cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D)== GLFW_PRESS){

						cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
				glfwSetWindowShouldClose(window, true);
		}
}

void Camera::updateCamera(GLFWwindow *window){
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}


void Camera::handleMouseMovement(double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    // Fixed: your original had pitch > 80.0f setting to 89.0f
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::handleMouseScroll(double yoffset){
    fov -= (float)yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

