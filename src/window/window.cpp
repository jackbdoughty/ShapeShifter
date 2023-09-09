#include "window.h"

#include <utility>

float PI = 3.14159265358979323846264338327950288;
double Zoom = PI / 3;
std::vector<Key> Keys(350);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!Keys[key].down) {
		Keys[key].pressed = (action == 2) ? 0 : action; // If the key was pressed, but not currently down
	}
	
	Keys[key].down = (action == 2) ? 0 : action; // If key down

}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

	Zoom += yoffset * PI / 180;

}

void mouseCallback(GLFWwindow* window, int key, int action, int mods) {
	keyCallback(window, key, -1, action, mods);

}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window(std::string txt) : m_Caption(std::move(txt)), m_Self(){
    
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_WIDTH = mode->width;
	m_HEIGHT = mode->height;

	createWindow();
	makeContextCurrent();
	setInputMode(GLFW_CURSOR, -1);
	setListeners({
		GLFW_MOUSE_BUTTON_1,
		GLFW_KEY_ESCAPE,
	});

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); //Initialise glad

}

void Window::createWindow() {

	m_Self = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_Caption.c_str(), m_Fullscreen ? glfwGetPrimaryMonitor() : GL_FALSE, GL_FALSE);
	glfwSetFramebufferSizeCallback(m_Self, frameBufferSizeCallback);

}

bool Window::keyPressed(int key) {

	if (Keys[key].pressed) {

		Keys[key].pressed = 0;

		return true;
	}

	return false;

}

void Window::setAngle(double sensitivity, Vector shapepos, Vector camerapos) {

	getMouseCoordinates(m_MouseX, m_MouseY);

	if (keyPressed(GLFW_MOUSE_BUTTON_1)) {

		m_LastMouseX = (float)m_MouseX;
		m_LastMouseY = (float)m_MouseY;

	}

	else if (keyDown(GLFW_MOUSE_BUTTON_1)) {

		double x = m_MouseX - m_LastMouseX;
		double y = m_MouseY - m_LastMouseY;
        double z = sensitivity * std::abs(shapepos.getLength() - camerapos.getLength()); // See writeup
		m_ThetaX = (float)atan(y / z);
		m_ThetaY = (float)atan(x / z);

	}

}

void Window::setAcceleration(bool g_AccelerationFlag, float g_Acceleration){

	if (g_AccelerationFlag) {

		float deceleration_x = -m_ThetaX / g_Acceleration;
		float deceleration_y = -m_ThetaY / g_Acceleration;

		m_ThetaX += deceleration_x;
		m_ThetaY += deceleration_y;
	}

	else {
		m_ThetaX = m_ThetaY = 0;
	}

	m_LastMouseX = (float)m_MouseX;
	m_LastMouseY = (float)m_MouseY;

}

bool Window::keyDown(int key) {

	if (Keys[key].down) {
		return true;
	}

	return false;

}

bool Window::shouldClose() const {

	if (glfwWindowShouldClose(m_Self) || keyPressed(GLFW_KEY_ESCAPE)){
		return true;
	}

	return false;

}

void Window::queryFullscreen() {

	if (keyPressed(GLFW_KEY_F11)) {

		m_Fullscreen = !m_Fullscreen;

		glfwSetWindowMonitor(m_Self, m_Fullscreen ? nullptr : glfwGetPrimaryMonitor(), 0, 0, m_WIDTH, m_HEIGHT, -1);

	}

}

double Window::getZoom(double zoommin, double zoommax){

	if (zoommin > Zoom) {
		Zoom += (zoommin - Zoom);
	}
	else if (zoommax < Zoom) {
		Zoom -= (Zoom - zoommax);
	}

	// Zoom limits

	return Zoom;

}

void Window::setZoom(double zoom, double zoommin, double zoommax) {

	if (zoommin < zoom < zoommax) {
		Zoom = zoom;
	}

}

void Window::makeContextCurrent() const {
	glfwMakeContextCurrent(m_Self);
}

void Window::setInputMode(int mode, int value) const {
	glfwSetInputMode(m_Self, mode, value);
}

void Window::swapBuffers() const {
	glfwSwapBuffers(m_Self);
}

void Window::setListeners(const std::vector<int>& keys) const{

	glfwSetKeyCallback(m_Self, keyCallback);
	glfwSetMouseButtonCallback(m_Self, mouseCallback);
	glfwSetScrollCallback(m_Self, scrollCallback);

	for (int key : keys) {

		Keys[key] = (Key{ 0, 0 });

	}

}

void Window::getMouseCoordinates(double &xpos, double &ypos) const {

	glfwGetCursorPos(m_Self, &xpos, &ypos);

}

bool Window::nextFrame(double time, unsigned int g_FPS) {

	if (time - m_LastFrame > 1.0 / g_FPS) {

		m_LastFrame = time;
		return true;

	}

	return false;

}
