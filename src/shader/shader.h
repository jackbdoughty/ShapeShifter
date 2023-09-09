#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../mat-vec/mat-vec.h"

class Shader {
private:

	unsigned int m_ID;
	std::string m_VertexFP; // Filepath to vertex shader
	std::string m_FragmentFP; // Filepath to fragment shader

	int getUniformLocation(const std::string&) const; // Get ID for uniform, given its name
	static void checkErrors(unsigned int, const std::string&); // Error checking

public:

	Shader(std::string , std::string );
	~Shader();

	void bindShader() const;
	static void unbindShader() ;

	void setUniformVec3(const std::string&, const Vector& ) const;
	void setUniformMat4(const std::string&, const Matrix& ) const;
	void setUniformf(const std::string&, float) const;
};