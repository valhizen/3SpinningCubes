#ifndef CUBES_HPP
#define CUBES_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"
class Cube {
public:
  Cube(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
  void init();
  void Draw();

  unsigned int vertex_array_object;
  unsigned int vertext_buffer_object;
  glm::mat4 model;
  void animation(float radius, float speed, bool value);
  void setPosition(const glm::vec3 &newPosition);
  // To send while creating the model
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  bool isOrbiting = false;
  float orbitRadius = 0.0f;
  float orbitSpeed = 0.0f;

  glm::mat4 getModelMatrix(); // Each cube has its own model

  float getOrbitRadius() const { return orbitRadius; }
  float getOrbitSpeed() const { return orbitSpeed; }
};
#endif
