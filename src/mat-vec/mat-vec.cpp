#include "mat-vec.h"

#include <cmath>
#include <utility>

Vector::Vector(float self, int size) : m_Self({}), m_Size(size) {
	
	for (unsigned int i = 0; i < m_Size; i++) {
		m_Self.push_back(self);
	}

}

Vector::Vector(const std::vector <float>& self) : m_Self(self), m_Size(self.size()) {}

Vector Vector::getPop() const {

	Vector temp(m_Self);
	temp.m_Self.pop_back();
	return temp;

}

Vector Vector::getAppend(float n) const {

	Vector temp(m_Self);
	temp.m_Self.push_back(n);
	return temp;

}

int Vector::getSize(){

	m_Size = m_Self.size();
	return m_Size;

}

float Vector::getLength(){

	float n = 0;
	
	for (unsigned int i = 0; i < getSize(); i++) {

		n += m_Self[i] * m_Self[i];

	}

	return std::sqrt(n);

}
Vector Vector::getNormalise() {

	return getScale(1 / getLength());

}

Vector Vector::getScale(float n){
	
	Vector temp(0.0f, getSize());

	for (unsigned int i = 0; i < getSize(); i++) {

		temp.m_Self[i] = m_Self[i] * n;

	}

	return temp;

}

Vector Vector::getCross(Vector vec){

	if (vec.getSize() != 3 || getSize() != 3) return Vector(m_Self);
	
	return Vector({

		m_Self[1] * vec.m_Self[2] - m_Self[2] * vec.m_Self[1],
		-(m_Self[0] * vec.m_Self[2] - m_Self[2] * vec.m_Self[0]),
		m_Self[0] * vec.m_Self[1] - m_Self[1] * vec.m_Self[0]

	});

}
Vector Vector::getAdd(Vector vec) {

	if (vec.getSize() != getSize()) return Vector(m_Self);

	Vector temp(0.0f, getSize());

	for (unsigned int i = 0; i < getSize(); i++) {

		temp.m_Self[i] = m_Self[i] + vec.m_Self[i];

	}

	return temp;

}

float Vector::getDot(Vector vec){
	
	if (vec.getSize() != getSize()) return 0.0f;

	float n = 0;

	for (unsigned int i = 0; i < getSize(); i++) {

		n += m_Self[i] * vec.m_Self[i];

	}

	return n;

}

Matrix::Matrix(std::vector<std::vector<float>> self) : m_Self(self), m_Size(self.size()) {}

Matrix::Matrix(float self, int size) : m_Size(size) {

	// Self is the diagonal number in the matrix.
	//So if self == 1, the matrix is the identity matrix

	for (unsigned int i = 0; i < m_Size; i++) {

		std::vector <float> temp = {};

		for (unsigned int j = 0; j < m_Size; j++) {

			if (i == j) {
				temp.push_back(self);
			}

			else {
				temp.push_back(0.0f);
			}

		}

		m_Self.push_back(temp);

	}

}

Matrix Matrix::getRotate(float angle, Vector rotationaxis) {

	// The rotation axis determines how much of the angle is applied in each axis

	if (getSize() != 4 || rotationaxis.getSize() != 3) return Matrix(m_Self);

	float x_angle = angle * rotationaxis.m_Self[0];
	float y_angle = angle * rotationaxis.m_Self[1];
	float z_angle = angle * rotationaxis.m_Self[2];

	float a = sinf(x_angle);
	float b = cosf(x_angle);

	float c = sinf(y_angle);
	float d = cosf(y_angle);

	float e = sinf(z_angle);
	float f = cosf(z_angle);

	return getMultiply(Matrix({

		{d * f, -d * e, -c, 0},
		{a * c * f + b * e, b * f - a * c * e, a * d, 0},
		{b * c * f - a * e, -a * f - b * c * e, b * d, 0},
		{0, 0, 0, 1}

		})); // See writeup for derivation
}

Matrix Matrix::getMultiply(Matrix mat) {

	if (getSize() != mat.getSize()) return Matrix(m_Self);

	Matrix temp(0.0f, getSize());

	for (unsigned int i = 0; i < getSize(); i++) {

		for (unsigned int j = 0; j < getSize(); j++) {

			for (unsigned int k = 0; k < getSize(); k++) {

				temp.m_Self[i][j] += m_Self[i][k] * mat.m_Self[k][j];

			}

		}

	}

	/*
	
	[a, b] * [x, y] = [ax + bz, ay + bw]
	[c, d]	 [z, w]   [cx + dz, cy + dw]
	
	*/

	return temp;

}

Vector Matrix::getMultiply(Vector vec) {

	if (vec.getSize() != getSize()) return vec;

	Vector temp(0.0f, vec.getSize());

	for (unsigned int i = 0; i < getSize(); i++) {

		for (unsigned int j = 0; j < getSize(); j++) {

			temp.m_Self[i] += m_Self[i][j] * vec.m_Self[j];

		}

	}

	return temp;

	/*
	 
	[a, b] * [x] = [ax + by]
	[c, d]	 [y]   [cx + dy]

	*/

}

int Matrix::getSize() {

	m_Size = m_Self.size();
	return m_Size;

}

Matrix Matrix::getPerspective(float fovy, float ratio, float near, float far){

	float f = 1 / cosf(fovy / 2);

	return getMultiply(Matrix({

		{f / ratio, 0, 0, 0},
		{0, f, 0, 0},
		{0, 0, (far + near) / (near - far), -1},
		{0, 0, (2 * far * near) / (near - far), 0}

	}));

	// From https://www.ibm.com/docs/en/aix/7.1?topic=library-gluperspective-subroutine

}

Matrix Matrix::getLookAt(Vector eye, Vector target, Vector up){

	Vector zaxis = target.getAdd(eye.getScale(-1)).getNormalise();
	Vector xaxis = zaxis.getCross(std::move(up)).getNormalise();
	Vector yaxis = xaxis.getCross(zaxis);

	zaxis = zaxis.getScale(-1);

	return getMultiply(Matrix({

		{xaxis.m_Self[0], yaxis.m_Self[0], zaxis.m_Self[0], 0},
		{xaxis.m_Self[1], yaxis.m_Self[1], zaxis.m_Self[1], 0},
		{xaxis.m_Self[2], yaxis.m_Self[2], zaxis.m_Self[2], 0},
		{-xaxis.getDot(eye), -yaxis.getDot(eye), -zaxis.getDot(eye), 1}

	}));

	// From https://www.ibm.com/docs/en/aix/7.1?topic=library-glulookat-subroutine

}

Matrix Matrix::getTranslate(Vector vec) {

	Matrix temp(1.0f, getSize());

	if (vec.getSize() != getSize() - 1.0) return Matrix(m_Self);

	for (int i = 0; i < getSize() - 1.0; i++) {
		
		temp.m_Self[i][getSize() - 1.0] = vec.m_Self[i];

	}

	return getMultiply(temp);

}