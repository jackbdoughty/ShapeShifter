#include "vb.h"

#include <utility>

void VertexBuffer::FillBuffer(std::vector <float> buffer, unsigned int size){

	m_Buffer = std::move(buffer);
	m_Size = size; // In bits

	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, m_Size, &m_Buffer[0], GL_STATIC_DRAW);
	// Create and pass data to vertex buffer

}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::bindBuffer() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbindBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, -1);
}
