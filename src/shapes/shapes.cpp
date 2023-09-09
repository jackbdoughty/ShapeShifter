#include "shapes.h"

#include <utility>

Shape::Shape(Vector pos, Vector col) : m_Position(std::move(pos)), m_Colour(std::move(col)), m_IBO(){};

void Shape::Create(const std::vector <float>& verticies, const std::vector <float>& indicies) {

	m_VBO.FillBuffer(verticies, verticies.size() * sizeof(float)); // Create vertex buffer
	m_IBO.FillBuffer(indicies, indicies.size()); // Create index buffer

	m_VBO.bindBuffer();

	m_Layout.pushElement(3,float(1.0)); // Vertices
	m_Layout.pushElement(3,float(1.0)); // Normals

	m_VAO.addBuffer(m_VBO, m_Layout); // Attach vertex buffer to vertex array
	m_VAO.bindArray();

	m_IBO.bindBuffer();
	m_VBO.unbindBuffer();
};