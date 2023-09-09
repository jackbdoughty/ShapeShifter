#include "ib.h"

void IndexBuffer::FillBuffer(std::vector <float> buffer, unsigned int count) {
	m_Count = count;
	glGenBuffers(1, &m_ID); // Create a new buffer, giving the ID as a pointer to be given a value
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); // Tell OpenGL it is an index buffer
	std::vector<int> newbuffer(buffer.begin(), buffer.end());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), &newbuffer[0], GL_STATIC_DRAW);
	// Pass the buffer into main memory, giving the size of the buffer in bits
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_ID); // Destructor
}

void IndexBuffer::bindBuffer() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::unbindBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, -1);
}

unsigned int IndexBuffer::getCount() const {
	return m_Count;
}
