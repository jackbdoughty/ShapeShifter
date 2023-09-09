/*

The vertex buffer stores all the information, about each vertex. In this case this is
its local coordinates, and the normal vector to the plane of which the vertex is associated with, but
it can be used to store many other types of data, such as colour.

*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

class VertexBuffer {
private:
	unsigned int m_ID;
	unsigned int m_Size;
	std::vector <float> m_Buffer;
public:
	void FillBuffer(std::vector<float>, unsigned int);
	~VertexBuffer();

	void bindBuffer() const;
	static void unbindBuffer() ;
};