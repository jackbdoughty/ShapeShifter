/*

The vertex array is an umbrella for all the previously objects that contribute to the graphics
pipeline, the vertex and index buffer and the vertex buffer layout. It tells OpenGl exactly how to
render each individual shape, so for each shape object in my program, they have their own VAO.

*/

#pragma once

#include "../vb/vb.h"
#include "../vbl/vbl.h"

class VertexArray {
private:
	unsigned int m_ID{};
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const; // Attach new buffer to vertex array
	void bindArray() const;
	static void unbindArray() ;
};