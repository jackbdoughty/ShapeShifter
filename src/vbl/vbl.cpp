#include "vbl.h"

unsigned int VertexBufferElement::getSizeofType(unsigned int type) {

	switch (type) {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        default: return 0;
	}

}

void VertexBufferLayout::pushElement(unsigned int count) {
	//static_assert(false); // If no type, give an error
}

void VertexBufferLayout::pushElement (unsigned int count, float) {
	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::getSizeofType(GL_FLOAT);
}

void VertexBufferLayout::pushElement (unsigned int count, unsigned int) {
	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_INT);
}

void VertexBufferLayout::pushElement (unsigned int count,unsigned char) {
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	m_Stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_BYTE);
}

unsigned int VertexBufferLayout::getStride() const {
	return m_Stride;
}

std::vector <VertexBufferElement> VertexBufferLayout::getElements() const {
	return m_Elements;
}