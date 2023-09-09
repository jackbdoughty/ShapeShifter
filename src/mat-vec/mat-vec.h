#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class Vector {

public:

	explicit Vector(float = 0.0f, int = 3);
	explicit Vector(const std::vector <float>&);

	std::vector <float> m_Self;

	Vector getPop() const; // Remove last item in the vector e.g (i, j, k) => (i, j)
	Vector getAppend(float) const; // Add an item to the end of the vector e.g (i, j) => (i, j, k)
	int getSize(); // Amount of items in vector
	float getLength(); // Return the magnitude of the vector
	Vector getNormalise(); // Return the normalised version of the vector
	Vector getScale(float); // Multiply each component in the vector by a scalar
	Vector getCross(Vector); // Perform the cross product between two 3-Vectors
	Vector getAdd(Vector); // Add two vectors
	float getDot(Vector); // Perform the dot product between two vectors

private:

	int m_Size;

};

class Matrix {

public:

	explicit Matrix(float = 1.0f, int = 4);
	explicit Matrix(std::vector <std::vector <float>>);

	std::vector <std::vector <float>> m_Self;

	Matrix getRotate(float, Vector); // Create a 4x4 rotation matrix
	Matrix getMultiply(Matrix); // Multiply two matrices
	Vector getMultiply(Vector); // Multiply a vector by a matrix
	Matrix getTranslate(Vector); // Create a translation matrix, given a vector to translate by
	int getSize(); // All matrices are square in this context so return the size of one side of the matrix
	Matrix getPerspective(float, float, float, float); // Create a perspective transformation matrix
	Matrix getLookAt(Vector, Vector, Vector); // Create a view transformation matrix

private:

	int m_Size;

};