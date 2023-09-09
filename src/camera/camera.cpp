#include "camera.h"

int Camera::setNextCameraPosition(int pos) {

	std::map <int, Position> Positions{

	{ 0, {Vector({1.0f, 1.0f, 3.0f}), Vector({0.0f, 1.0f, 0.0f}), "Idle" }},
	{ 1, {Vector({0.0f,3.0f,0.0f}), Vector({0.0f, 0.0f, 1.0f}), "Top" } },
	{ 2, {Vector({0.0f,0.0f,3.0f}),  Vector({0.0f, 1.0f, 0.0f}), "Front" } },
	{ 3, {Vector({3.0f,0.0f,0.0f}), Vector({0.0f, 1.0f, 0.0f}), "Side 1" } },
	{ 4, {Vector({-3.0f,0.0f,0.0f}), Vector({0.0f, 1.0f, 0.0f}), "Side 2" } },
	{ 5, {Vector({0.0f,0.0f,-3.0f}), Vector({0.0f, 1.0f, 0.0f}), "Back" } },
	{ 6, {Vector({0.0f,-3.0f,0.0f}), Vector({0.0f, 0.0f, -1.0f}), "Bottom" } }
	};
	// Map of all the different camera positions/elevations

	if (pos == Positions.size() - 1) {
		pos = 0;
		m_NextPositionName = Positions[1].m_Name;
	}
	// If position is 6, the next position will be 0

	else {

		pos++;

		if (pos == Positions.size() - 1) {
			m_NextPositionName = Positions[0].m_Name;
		}
		// If position is 6, the next position name will be 'Idle'

		else {
			m_NextPositionName = Positions[pos + 1].m_Name;
		}
		// Otherwise, the next position name is the name of the position with an index one greater than the current

	}

	m_Position = Positions[pos].m_Position;
	m_Up = Positions[pos].m_Up;
	// Reset the position and up vector

	return pos;
	// Return new position of the camera

}