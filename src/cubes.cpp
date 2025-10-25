#include "cubes.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/trigonometric.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include <iostream>

Cube::Cube(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
  rotation = rot;
  position = pos;
  scale = scl;
  isOrbiting = false;
  orbitRadius = 0.0f;
  orbitSpeed = 0.0f;

  init();
}
void Cube::init() {

  float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.5f,  -0.5f, -0.5f,
                      1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  0.5f,
                      0.5f,  -0.5f, 1.0f,  1.0f,

                      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  -0.5f, -0.5f, -0.5f,
                      0.0f,  0.0f,

                      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
                      1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.5f,
                      0.5f,  0.5f,  1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,
                      1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,

                      -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
                      1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -0.5f,
                      -0.5f, -0.5f, 0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
                      0.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,

                      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
                      1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,
                      -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
                      0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

                      -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,  -0.5f, -0.5f,
                      1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.5f,
                      -0.5f, 0.5f,  1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
                      0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,

                      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.5f,  0.5f,  -0.5f,
                      1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.5f,
                      0.5f,  0.5f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,
                      0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f

  };
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);
  // Creating an ID
  // We bind the buffer
  glGenBuffers(1, &vertext_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, vertext_buffer_object);
  // copies previously defined vertex data into buffer memory
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
  glEnableVertexAttribArray(0);
}

void Cube::Draw() {
  glBindVertexArray(vertex_array_object);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

glm::mat4 Cube::getModelMatrix() {
  model = glm::mat4(1.0f);
  // Translate the cube and change the position
  if (isOrbiting && orbitRadius > 0.0f) {
    float angle = static_cast<float>(glfwGetTime()) * orbitSpeed;
    glm::vec3 orbitPos;
    orbitPos.x = orbitRadius * cos(angle);
    orbitPos.y = 0.0f;
    orbitPos.z = orbitRadius * sin(angle);
    model = glm::translate(model, orbitPos);

    static int debugCount = 0;
    if (debugCount < 5) {
      std::cout << "Orbit - Radius: " << orbitRadius << " Angle: " << angle
                << " Pos: (" << orbitPos.x << ", " << orbitPos.y << ", "
                << orbitPos.z << ")" << std::endl;
      debugCount++;
    }
  } else {
    model = glm::translate(model, position);
  }

  model =
      glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  model =
      glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  model =
      glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, scale);

  return model;
}

void Cube::animation(float radius, float speed, bool value) {
  orbitRadius = radius;
  orbitSpeed = speed;
  isOrbiting = value;
  std::cout << "Animation set - Radius: " << radius << " Speed: " << speed
            << " Orbiting: " << (value ? "true" : "false") << std::endl;
}
