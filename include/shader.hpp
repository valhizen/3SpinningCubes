#ifndef SHADER_HPP
#define SHADER_HPP

#include "glm/glm.hpp"

class Shader{
public:
		int ID;
		Shader(const char* vertexPath, const char* fragmentPart);
		void use();

		void setMat4(const char* string, glm::mat4 data);
};



#endif
