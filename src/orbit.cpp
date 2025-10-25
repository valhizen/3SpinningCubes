#include "orbit.hpp"
#include "glad/glad.h"
#include <iostream>
#include <vector>
#include <cmath>

OrbitPath::OrbitPath(float radius, float numSegments) : segments(numSegments){
std::vector<float> vertices;
    
    for (int i = 0; i <= numSegments; i++) {
              float angle = (2.0f * M_PI * i) / numSegments;
        float x = radius * cos(angle);
        float y = 0.0f;
        float z = radius * sin(angle);
        
        if (i < 3) {  // Print first 3 points
            std::cout << "Point " << i << ": (" << x << ", " << y << ", " << z << ")" << std::endl;
        }
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }
    
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    
    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 
                 vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void OrbitPath::Draw(){
    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_LINE_LOOP, 0, segments + 1);
}
