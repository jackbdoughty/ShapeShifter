#pragma once

#include <map>
#include "../mat-vec/mat-vec.h"
#include "../shapes/shapes.h"

struct Position {

public:

	Vector m_Position;
	Vector m_Up;
	std::string m_Name;

};

class Camera {
public:

	int setNextCameraPosition(int);

	Camera() : m_Position(Vector({ 1.0f, 1.0f, 3.0f })), m_Up(Vector({ 0.0f, 1.0f, 0.0f })), m_NextPositionName("Top") {};

	Vector m_Position;
	Vector m_Up;
	std::string m_NextPositionName;
	
};