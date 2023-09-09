#include "va.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_ID); // Create
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_ID); // Destroy
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const {

	bindArray();
	vb.bindBuffer();
	const auto& elements = layout.getElements();	
	//Layout is coordinates and normals in this context

    int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];

		glEnableVertexAttribArray(i); // Assign properties to each vertex, e.g coordinates and normals
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (void*)(size_t)offset);
		// Stide is the size of the vertex, e.g a coordinate (1.0f, 1.0f, 0.02f) would have size of 3 x sizeof(float) in bytes
		
		offset += element.count * VertexBufferElement::getSizeofType(element.type);
		// Offset determines how far through the vertex the element is, in bytes

	}

}

void VertexArray::bindArray() const {
	glBindVertexArray(m_ID);
}

void VertexArray::unbindArray() {
	glBindVertexArray(-1);
}
