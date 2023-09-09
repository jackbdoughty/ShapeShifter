#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../va/va.h"
#include "../vb/vb.h"
#include "../ib/ib.h"
#include "../vbl/vbl.h"
#include "../mat-vec/mat-vec.h"

struct Properties {

	const char* m_Name;
	const char* m_SurfaceArea;
	const char* m_Volume;

};

class Shape {
public:

	explicit Shape(Vector = Vector(0.0f, 3), Vector = Vector({ 0.0f, 0.0f, 0.0f }));
	void Create(const std::vector <float>&, const std::vector <float>&);

	Vector m_Position; // Position of shape
	Vector m_Colour; // Colour of shape
	std::vector <float> m_Vertices; // Shape vertices
	std::vector <float> m_Indices; // Index array specific to shape
	float m_Matteness = 0.5;

	Properties m_Properties = {

		"",
		"",
		""

	};

	VertexArray m_VAO; // Vertex array
	VertexBufferLayout m_Layout; // Vertex buffer layout
	IndexBuffer m_IBO; // Index buffer
	VertexBuffer m_VBO; // Vertex buffer
};

// Cube inherits from Shape

class Cube : public Shape {

	using Shape::Shape;

public:
	
	std::vector <float> m_Vertices = {

		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	std::vector <float> m_Indices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	Properties m_Properties = {

		"Cube",
		"6 x Width x Height",
		"Width x Height x Depth"

	}; // Description
	
};

class Pyramid : public Shape {
	
	using Shape::Shape;

public:

	std::vector <float> m_Vertices = {

		-0.5f, -0.4f,  0.5f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.4f, -0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.4f, -0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.4f,  0.5f,  0.0f, -1.0f, 0.0f,
				
		-0.5f, -0.4f,  0.5f, -0.8f, 0.5f,  0.0f,
		-0.5f, -0.4f, -0.5f, -0.8f, 0.5f,  0.0f,
		 0.0f,  0.4f,  0.0f, -0.8f, 0.5f,  0.0f,
				
		-0.5f, -0.4f, -0.5f,  0.0f, 0.5f, -0.8f,
		 0.5f, -0.4f, -0.5f,  0.0f, 0.5f, -0.8f,
		 0.0f,  0.4f,  0.0f,  0.0f, 0.5f, -0.8f,
				
		 0.5f, -0.4f, -0.5f,  0.8f, 0.5f,  0.0f,
		 0.5f, -0.4f,  0.5f,  0.8f, 0.5f,  0.0f,
		 0.0f,  0.4f,  0.0f,  0.8f, 0.5f,  0.0f,
				
		 0.5f, -0.4f,  0.5f,  0.0f, 0.5f,  0.8f,
		-0.5f, -0.4f,  0.5f,  0.0f, 0.5f,  0.8f,
		 0.0f,  0.4f,  0.0f,  0.0f, 0.5f,  0.8f
	};

	std::vector <float> m_Indices = {
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		7, 9, 8,
		10, 12, 11,
		13, 15, 14
	};

	Properties m_Properties = {

		"Pyramid",
		"Width" u8"\u00B2" " + 2 x Width x Slant Height",
		// ImGui only supports UTF-8 so have to specify a squared symbol as such
		"Height x Width x Depth / 3"

	};

};

class Cuboid : public Shape {

	using Shape::Shape;

public:

	std::vector <float> m_Vertices = {

		-1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-1.0f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 1.0f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 1.0f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-1.0f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-1.0f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-1.0f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-1.0f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-1.0f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 1.0f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 1.0f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 1.0f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 1.0f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

		-1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	std::vector <float> m_Indices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	Properties m_Properties = {

		"Cuboid",
		"4 x Width x Height + 2 x Height x Depth",
		"Width x Height x Depth"

	};

};

class TriPrism : public Shape {

	using Shape::Shape;

public:

	std::vector <float> m_Vertices = {

		-1.0f, -0.4f,  0.5f,  0.0f, -1.0f, 0.0f,
		-1.0f, -0.4f, -0.5f,  0.0f, -1.0f, 0.0f,
		 1.0f, -0.4f, -0.5f,  0.0f, -1.0f, 0.0f,
		 1.0f, -0.4f,  0.5f,  0.0f, -1.0f, 0.0f,
		 //bottom

		-1.0f, -0.4f, -0.5f, 0.0f, 0.5f, -0.8f,
		 1.0f, -0.4f, -0.5f, 0.0f, 0.5f, -0.8f,
		 1.0f,  0.4f,  0.0f, 0.0f, 0.5f, -0.8f,
		-1.0f,  0.4f,  0.0f, 0.0f, 0.5f, -0.8f,
		 //front side

		-1.0f, -0.4f, 0.5f,  0.0f, 0.5f, 0.8f,
		 1.0f, -0.4f, 0.5f,  0.0f, 0.5f, 0.8f,
		 1.0f,  0.4f, 0.0f,  0.0f, 0.5f, 0.8f,
		-1.0f,  0.4f, 0.0f,  0.0f, 0.5f, 0.8f,
		 //back side

		-1.0f, -0.4f,  0.5f, -1.0f, 0.0f,  0.0f,
		-1.0f, -0.4f, -0.5f, -1.0f, 0.0f,  0.0f,
		-1.0f,  0.4f,  0.0f, -1.0f, 0.0f,  0.0f,
		//left side

		1.0f, -0.4f,  0.5f, 1.0f, 0.0f,  0.0f,
		1.0f, -0.4f, -0.5f, 1.0f, 0.0f,  0.0f,
		1.0f,  0.4f,  0.0f, 1.0f, 0.0f,  0.0f,
		//right side
	};

	std::vector <float> m_Indices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 14, 13,

		15, 17, 16

	};

	Properties m_Properties = {

		"Triangular Prism",
		" = (2 x Slant Height + Width) Length + Width x Height",
		" = 0.5 x Height x Length x Width"

	};

};

class AxesX : public Shape {

	using Shape::Shape;

public:

	std::vector <float> m_Vertices = {

		-50.0f, -0.01f,  0.01f,  0.0f,  1.0f,  0.0f,
		 50.0f, -0.01f,  0.01f,  0.0f,  1.0f,  0.0f,
		 50.0f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f,
		-50.0f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f,
			    
		-50.0f, -0.01f, -0.01f,  0.0f, -1.0f,  0.0f,
		 50.0f, -0.01f, -0.01f,  0.0f, -1.0f,  0.0f,
		 50.0f,  0.01f, -0.01f,  0.0f, -1.0f,  0.0f,
		-50.0f,  0.01f, -0.01f,  0.0f, -1.0f,  0.0f,
			    
		-50.0f,  0.01f, -0.01f,  0.0f,  0.0f,  1.0f,
		 50.0f,  0.01f, -0.01f,  0.0f,  0.0f,  1.0f,
		 50.0f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,
		-50.0f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,

		-50.0f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f,
		 50.0f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f,
		 50.0f, -0.01f,  0.01f,  0.0f,  0.0f, -1.0f,
		-50.0f, -0.01f,  0.01f,  0.0f,  0.0f, -1.0f

	};

	std::vector <float> m_Indices = {

		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12

	};

};

class AxesY : public Shape {

	using Shape::Shape;

public:

	std::vector <float> m_Vertices = {

		-0.01f, -50.0f,  0.01f,  0.0f,  0.0f,  1.0f,
		-0.01f,  50.0f,  0.01f,  0.0f,  0.0f,  1.0f,
		 0.01f,  50.0f,  0.01f,  0.0f,  0.0f,  1.0f,
		 0.01f, -50.0f,  0.01f,  0.0f,  0.0f,  1.0f,
			    
		-0.01f, -50.0f, -0.01f,  0.0f,  0.0f, -1.0f,
		-0.01f,  50.0f, -0.01f,  0.0f,  0.0f, -1.0f,
		 0.01f,  50.0f, -0.01f,  0.0f,  0.0f, -1.0f,
		 0.01f, -50.0f, -0.01f,  0.0f,  0.0f, -1.0f,
			    
		 0.01f, -50.0f, -0.01f,  1.0f,  0.0f,  0.0f,
		 0.01f,  50.0f, -0.01f,  1.0f,  0.0f,  0.0f,
		 0.01f,  50.0f,  0.01f,  1.0f,  0.0f,  0.0f,
		 0.01f, -50.0f,  0.01f,  1.0f,  0.0f,  0.0f,
			    
		-0.01f, -50.0f, -0.01f, -1.0f,  0.0f,  0.0f,
		-0.01f,  50.0f, -0.01f, -1.0f,  0.0f,  0.0f,
		-0.01f,  50.0f,  0.01f, -1.0f,  0.0f,  0.0f,
		-0.01f, -50.0f,  0.01f, -1.0f,  0.0f,  0.0f
	};

	std::vector <float> m_Indices = {

		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12

	};

};

class AxesZ : public Shape {

	using Shape::Shape;

public:

	std::vector <float> m_Vertices = {

		-0.01f,  0.01f, -50.0f,  0.0f,  1.0f,  0.0f,
		-0.01f,  0.01f,  50.0f,  0.0f,  1.0f,  0.0f,
		 0.01f,  0.01f,  50.0f,  0.0f,  1.0f,  0.0f,
		 0.01f,  0.01f, -50.0f,  0.0f,  1.0f,  0.0f,
											   
		-0.01f, -0.01f, -50.0f,  0.0f, -1.0f,  0.0f,
		-0.01f, -0.01f,  50.0f,  0.0f, -1.0f,  0.0f,
		 0.01f, -0.01f,  50.0f,  0.0f, -1.0f,  0.0f,
		 0.01f, -0.01f, -50.0f,  0.0f, -1.0f,  0.0f,
					    
		 0.01f, -0.01f, -50.0f,  1.0f,  0.0f,  0.0f,
		 0.01f, -0.01f,  50.0f,  1.0f,  0.0f,  0.0f,
		 0.01f,  0.01f,  50.0f,  1.0f,  0.0f,  0.0f,
		 0.01f,  0.01f, -50.0f,  1.0f,  0.0f,  0.0f,
					    
		-0.01f, -0.01f, -50.0f, -1.0f,  0.0f,  0.0f,
		-0.01f, -0.01f,  50.0f, -1.0f,  0.0f,  0.0f,
		-0.01f,  0.01f,  50.0f, -1.0f,  0.0f,  0.0f,
		-0.01f,  0.01f, -50.0f, -1.0f,  0.0f,  0.0f
	};

	std::vector <float> m_Indices = {

		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12

	};

};