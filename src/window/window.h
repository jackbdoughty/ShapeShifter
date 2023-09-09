#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "../mat-vec/mat-vec.h"

struct Key {
	int pressed;
	int down;
};

class Window {
private:
	std::string m_Caption; // Top of screen text
	bool m_Fullscreen = false;
	double m_LastFrame = 0; //Time since last frame was rendered
	double m_MouseX{}; // Mouse X position
	double m_MouseY{}; // Mouse Y position
	float m_LastMouseX = 0; // Last mouse X position
	float m_LastMouseY = 0;	// Last mouse Y position

public:

	float m_ThetaX = 0; // Angle in X axes for shape rotation
	float m_ThetaY = 0; // Angle in Y axes for shape rotation
	GLFWwindow* m_Self;
	unsigned int m_WIDTH; // Window width
	unsigned int m_HEIGHT; // Window height

	explicit Window(std::string);
	void queryFullscreen(); // Check if fullscreen should be enabled
	static double getZoom(double, double); // Get the zoom value
	static void setZoom(double, double, double); // Set the zoom value, from user input
	void createWindow();
	static bool keyDown(int); // Check if the key given is currently pressed down
	static bool keyPressed(int); // Check if the key given has been pressed since last checked
	bool shouldClose() const; // Check if window should close
	void makeContextCurrent() const;
	void setInputMode(int, int) const;
	void swapBuffers() const; // Reset frame
	void setListeners(const std::vector<int>&) const; // Set key inputs to listen to, and what functions to use on clicked
	void getMouseCoordinates(double&, double&) const;
	void setAngle(double, Vector, Vector); // Set angles of rotation from user mouse input
	void setAcceleration(bool, float); // Controls the deceleration of the shape after being moved
	bool nextFrame(double, unsigned int); // Checks if the next frame is due (60FPS)
	
};