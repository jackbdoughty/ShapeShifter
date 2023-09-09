/*
* 
Using index buffers are not actually necessary in the graphics pipeline. The coordinates of each vertex of the shape could be listed
individually. However, this would lead to duplicate vertices, as only triangles are able to be drawn. 
So what the index buffer does is it tells OpenGL in what order to intepret the vertex buffer, given that duplicates have been removed.

e.g Consider a unit square.
This would have to rendered using two triangles of coordinates (0,0), (1,0), (1,1) and (0,0), (1,1), (1,0).
Two pairs of these coordinates are repeated, which, as is, doesn't waste alot of space, but with higher quality
3D objects it would. So it is important to remove duplicates. The coordinates are now (0,0), (0,1), (1,0) and (0,0).
But the triangles must still be accurately rendered, so each vertex is given an index, and the method of drawing the two
triangles is done by referencing these indexes.

	Vertices:		Index Buffer:
	
	0 => (0,0)		0, 1, 3, # Triangle 1 
	1 => (1,0)		3, 2, 0  # Triangle 2
	2 => (0,1)
	3 => (1,1)

The same technique is used in this program, however with 3D coordinates.

*/

#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer {
private:
	unsigned int m_ID; // Specific ID given to this new buffer
	unsigned int m_Count; // Amount of numbers going into the buffer 
public:
	void FillBuffer(std::vector <float>, unsigned int);
	~IndexBuffer();

	void bindBuffer() const;
	static void unbindBuffer() ;
	unsigned int getCount() const;
};
