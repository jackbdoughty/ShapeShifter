/*

The vertex buffer layout describes how the vertex buffer is set up, where the data goes and what type of data it is.
I touch on the stride and offset of an element in the vertex array file, but in more depth they are both simply
amounts of bytes that describe where in the vertex / array each data lies.

e.g, Assuming each value represents 1 byte each:
	
	[=============Vertex 0==============]
	|X  Y  Z  W|  |R  G  B  A|  |i  j  k|
	^ Position	  ^ Colour      ^ Normal
	offset = 0    offset = 4	offset = 8
	
	<----------------------------------->			  
		   Stride = 4 + 4 + 3 = 11
	
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

struct VertexBufferElement {

	unsigned int type;
	unsigned int count;
	unsigned char normalised;

	static unsigned int getSizeofType(unsigned int type);
};

class VertexBufferLayout {
private:

	std::vector <VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:

	VertexBufferLayout() : m_Stride(0) {};
	void pushElement(unsigned int);
    void pushElement (unsigned int,float);
    void pushElement (unsigned int,unsigned int);
    void pushElement (unsigned int,unsigned char);

	unsigned int getStride() const;
	std::vector <VertexBufferElement> getElements() const;
};