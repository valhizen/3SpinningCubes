#ifndef ORBIT_HPP
#define ORBIT_HPP

class OrbitPath{
public:
		OrbitPath(float radius, float segments);
		void Draw();
    int segments;

		unsigned int vertex_array_object;
		unsigned int vertex_buffer_object;
};



#endif
