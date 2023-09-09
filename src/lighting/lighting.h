#pragma once

#include "../mat-vec/mat-vec.h"

class LightSource {
public:
	
	explicit LightSource(const Vector& pos = Vector({ 0.0f, 0.0f, 0.0f }), float intensity = 0.5f) : m_Intensity(intensity), m_Position(pos), m_PositionOrigin(pos), m_Model(Matrix(1.0f)), m_Angles(Vector({ 0.0f, 0.0f, 0.0f })) {};
	float m_Intensity;
	Vector m_Position;
	Vector m_PositionOrigin;
	Matrix m_Model;
	Vector m_Angles;
};
