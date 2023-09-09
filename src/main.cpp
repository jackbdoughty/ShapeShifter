#define STB_IMAGE_IMPLEMENTATION
// Requried for stb library

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <stb/stb_image.h>
// Include libraries

#include "window/window.h"
#include "va/va.h"
#include "ib/ib.h"
#include "shader/shader.h"
#include "renderer/renderer.h"
#include "shapes/shapes.h"
#include "camera/camera.h"
#include "lighting/lighting.h"
#include "ImGui/myImGuiTheme.h"
#include "mat-vec/mat-vec.h"
// Include own files

class IO {

public:
	static ImGuiIO& get(const Window& window) {

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window.m_Self, true); // Initialising ImGui
		ImGui_ImplOpenGL3_Init("#version 330"); // Set ImGui shaders to version 3.3

		return ImGui::GetIO(); // Return ImGui input/output interface
	};

};

class ShapeShifter {
public:
	ShapeShifter() : // Constructor and member initialiser list

		g_WINDOW(Window("ShapeShifter")),
		g_Shader(Shader("../src/shaders/shape/vertex.shader", "../src/shaders/shape/fragment.shader")),
		g_IO(IO::get(g_WINDOW)),
		g_Cube(Cube(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 0.4f, 1.0f, 1.0f }))),
		g_Pyramid(Pyramid(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 0.4f, 1.0f, 1.0f }))),
		g_Cuboid(Cuboid(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 0.4f, 1.0f, 1.0f }))),
		g_TriPrism(TriPrism(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 0.4f, 1.0f, 1.0f }))),
		g_FONT(g_IO.Fonts->AddFontFromFileTTF("../res/Helvetica.ttf", 25)),
		g_HEADERFONT(g_IO.Fonts->AddFontFromFileTTF("../res/Helvetica.ttf", 30)),
		g_TITLEFONT(g_IO.Fonts->AddFontFromFileTTF("../res/Helvetica-Bold.ttf", 30)),
		g_Camera(Camera()),
		g_Light(LightSource(Vector({ 0.0f, 0.0f, 3.0f }))),
		g_Model(Matrix()),
		g_View(Matrix(1.0f)),
		g_Projection(Matrix(1.0f)),
		g_AxesX(AxesX(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 1.0f, 0.0f, 0.0f }))),
		g_AxesY(AxesY(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 0.0f, 1.0f, 0.0f }))),
		g_AxesZ(AxesZ(Vector({ 0.0f, 0.0f, 0.0f }), Vector({ 0.0f, 0.0f, 1.0f }))),
        g_Shape(),
        g_ICON()

	{
		flagsInit();
		iconInit("../res/Icon1.png");
		shapesInit();

		// Must be run before main, so included in constructor

	};

	void Main() {

		while (!g_WINDOW.shouldClose()) { // Checks if window should close

			if (g_WINDOW.nextFrame(glfwGetTime(), g_FPS)) { // Checks if the next frame is due (60FPS)

				glfwPollEvents(); // Process GLFW events, e.g resizing the screen
				imGuiLoop(); // Creates the ImGui GUI
				userInput(); // Takes input from the user and performs calculations, ready for it to be sent to the shader
				pipeToShader(); // Send dynamic data to the shader, as 'uniforms'
				drawShape(); // Draw the currently selected shape
				drawAxis(); // Draw the axis

			}

		}

		terminateWindow(); // End the program

	}

	static void flagsInit() {

		glEnable(GL_DEPTH_TEST); 
		/*So that faces of the shape, that were defined before others,
		are not incorrectly drawn ontop of faces that should be closest to the camera*/
		
		glEnable(GL_MULTISAMPLE); // To prevent screen tearing (VSYNC)

	};

	void shapesInit() {

		g_Cube.Create(g_Cube.m_Vertices, g_Cube.m_Indices);
		g_Pyramid.Create(g_Pyramid.m_Vertices, g_Pyramid.m_Indices);
		g_Cuboid.Create(g_Cuboid.m_Vertices, g_Cuboid.m_Indices);
		g_TriPrism.Create(g_TriPrism.m_Vertices, g_TriPrism.m_Indices);
		g_AxesX.Create(g_AxesX.m_Vertices, g_AxesX.m_Indices);
		g_AxesY.Create(g_AxesY.m_Vertices, g_AxesY.m_Indices);
		g_AxesZ.Create(g_AxesZ.m_Vertices, g_AxesZ.m_Indices);

		g_Shape = &g_Cube; // Dynamically allocates the chosen shape to a general shape object
		g_Shape->m_Properties = g_Cube.m_Properties;

	};

	void iconInit(const char *fp) {

		g_ICON[0].pixels = stbi_load(fp, &g_ICON[0].width, &g_ICON[0].height, nullptr, STBI_rgb_alpha);
		//Load the window icon from local files

		glfwSetWindowIcon(g_WINDOW.m_Self, 1, g_ICON); // Set the icon
		stbi_image_free(g_ICON[0].pixels); // Free up memory space occupied by the icon

	};

	void userInput() {

		g_WINDOW.setAngle((double)g_Sensitivity, g_Shape->m_Position, g_Camera.m_Position);
		/* Find the angle of shape rotation, governed by the mouse sensitivity, distance between the cameraand the shape
		and the distance travelled by the mouse while it is held down */

		g_Model = g_Model.getTranslate(g_Shape->m_Position); // Move the shape to its world coordinates

		if (!g_IO.WantCaptureMouse) { // If the mouse isn't over a ImGui interface

			g_Model = g_Model.getRotate(g_WINDOW.m_ThetaX, Vector({ 1.0f, 0.0f, 0.0f }));
			g_Model = g_Model.getRotate(g_WINDOW.m_ThetaY, Vector({ 0.0f, 1.0f, 0.0f }));
			// Rotate the shape in the x and y axis, given the calculated angles

		}

		g_WINDOW.setAcceleration(g_AccelerationFlag, g_Acceleration); 
		/* If acceleration is on, set the shape to decelerate after the mouse is let go */

		g_Projection = Matrix(1.0f);
		g_Projection = g_Projection.getPerspective(2 * (float)Window::getZoom(g_MinZoom, g_MaxZoom), (float)g_WINDOW.m_WIDTH / (float)g_WINDOW.m_HEIGHT, 0.1f, 100.0f);
		// Create a perspective transformation, to make the scene look three-dimensional

		g_Light.m_Model = Matrix(1.0f);
		g_Light.m_Model = g_Light.m_Model.getRotate(g_Light.m_Angles.m_Self[0], Vector({ 1.0f, 0.0f, 0.0f }));
		g_Light.m_Model = g_Light.m_Model.getRotate(g_Light.m_Angles.m_Self[1], Vector({ 0.0f, 1.0f, 0.0f }));
		g_Light.m_Model = g_Light.m_Model.getRotate(g_Light.m_Angles.m_Self[2], Vector({ 0.0f, 0.0f, 1.0f }));
		// Rotate the light source around the x, y and z axis given the angles the user has provided in the GUI

		g_Light.m_Position = g_Light.m_Model.getMultiply(g_Light.m_PositionOrigin.getAppend(1.0f)).getPop();
		// The light position must be altered to be a 4-Vector to be multiplied by its model matrix, then back to a 3-Vector

		g_View = Matrix(1.0f);
		g_View = g_View.getLookAt(g_Camera.m_Position, g_Shape->m_Position, g_Camera.m_Up);
		// Calculate the view transformation, so the camera looks at the centre of the shape

	};

	void pipeToShader() {

		g_Shader.bindShader();

		g_Shader.setUniformMat4("model", g_Model);
		g_Shader.setUniformVec3("shapeColour", g_Shape->m_Colour);
		g_Shader.setUniformf("lightIntensity", g_Light.m_Intensity);
		g_Shader.setUniformVec3("lightPos", g_Light.m_Position);
		g_Shader.setUniformVec3("viewPos", g_Camera.m_Position);
		g_Shader.setUniformf("specularStrength", g_Shape->m_Matteness);
		g_Shader.setUniformMat4("projection", g_Projection);
		g_Shader.setUniformf("offset", g_Offset);
		g_Shader.setUniformMat4("view", g_View);

	};

	void drawShape() {

		Renderer::drawElements(g_Shape->m_VAO, g_Shape->m_IBO, g_Shader);
		// Pass the shape's vertex array, index array and shaders

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Draw ImGui's GUI

		g_WINDOW.swapBuffers();
		Renderer::clearBuffer();
		// Clear the screen and prepare for the next frame

	};

	void drawAxis() {

		g_Shader.setUniformMat4("model", Matrix());
		g_Shader.setUniformVec3("lightPos", Vector());
		g_Shader.setUniformf("lightIntensity", 0.4f);

		if (g_CameraPosition != 3 && g_CameraPosition != 4) { // If the camera is looking along the X axes then don't draw it
			g_AxesX.m_VAO.bindArray();
			g_Shader.setUniformVec3("shapeColour", g_AxesX.m_Colour);
			Renderer::drawElements(g_AxesX.m_VAO, g_AxesX.m_IBO, g_Shader);
		}

		if (g_CameraPosition != 1 && g_CameraPosition != 6) { // '' Y axes ''
			g_AxesY.m_VAO.bindArray();
			g_Shader.setUniformVec3("shapeColour", g_AxesY.m_Colour);
			Renderer::drawElements(g_AxesY.m_VAO, g_AxesY.m_IBO, g_Shader);
		}

		if (g_CameraPosition != 2 && g_CameraPosition != 5) { // '' Z axes ''
			g_AxesZ.m_VAO.bindArray();
			g_Shader.setUniformVec3("shapeColour", g_AxesZ.m_Colour);
			Renderer::drawElements(g_AxesZ.m_VAO, g_AxesZ.m_IBO, g_Shader);
		}

		g_Shape->m_VAO.bindArray();

	}

	static void terminateWindow() {

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();

	};

	void imGuiLoop() {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::SetNextWindowSize({ (float)(g_WINDOW.m_WIDTH * g_Offset), (float)g_WINDOW.m_HEIGHT });

		ImGui::PushFont(g_TITLEFONT);

		ImGuiTheme Theme;
		Theme.changePallette(ImVec4(g_Shape->m_Colour.m_Self[0], g_Shape->m_Colour.m_Self[1], g_Shape->m_Colour.m_Self[2], 0.2));
		//Change cololur scheme based on the colour of the shape 

		if (ImGui::Begin("[START]", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
		
			ImGui::PopFont();
			ImGui::PushFont(g_HEADERFONT);

			if (ImGui::TreeNode("Shapes")) {

				ImGui::PushFont(g_FONT);
				
				if (ImGui::Button("Cube")) {

					imGuiSwapShape(g_Cube);
					g_Shape->m_Properties = g_Cube.m_Properties;

				}

				if (ImGui::Button("Pyramid")) {

					imGuiSwapShape(g_Pyramid);
					g_Shape->m_Properties = g_Pyramid.m_Properties;

				}

				if (ImGui::Button("Cuboid")) {

					imGuiSwapShape(g_Cuboid);
					g_Shape->m_Properties = g_Cuboid.m_Properties;

				}

				if (ImGui::Button("Triangular Prism")) {

					imGuiSwapShape(g_TriPrism);
					g_Shape->m_Properties = g_TriPrism.m_Properties;

				}

				if (ImGui::Button("Reset Position")) {
					g_Model = Matrix(1.0f);
				}

				if (ImGui::TreeNodeEx("Matteness", ImGuiTreeNodeFlags_NoTreePushOnOpen))
				{

					ImGui::PushID(0);
					ImGui::TextWrapped("");
					ImGui::SliderFloat("", &g_Shape->m_Matteness, 2.0f, 0.0f, "", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::TextWrapped("");
					ImGui::PopID();

				}

				ImGui::PushItemWidth(g_WidgetWidth * g_WINDOW.m_WIDTH);

				if (ImGui::TreeNodeEx("Shape Colour", ImGuiTreeNodeFlags_NoTreePushOnOpen))
				{

					ImGui::PushID(1);
					ImGui::TextWrapped("");
					ImGui::ColorPicker3("", &g_Shape->m_Colour.m_Self[0], ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayHSV);
					ImGui::TextWrapped("");
					ImGui::PopID();

				}

				ImGui::PopItemWidth();
				ImGui::PopFont();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Camera"))
			{

				ImGui::PushFont(g_FONT);

				if (ImGui::Button(g_Camera.m_NextPositionName.c_str())) {
					g_CameraPosition = g_Camera.setNextCameraPosition(g_CameraPosition);
				}

				ImGui::PushItemWidth(g_WidgetWidth * g_WINDOW.m_WIDTH);

				if (ImGui::TreeNodeEx("Zoom", ImGuiTreeNodeFlags_NoTreePushOnOpen))
				{

					auto zoom = (float)Window::getZoom(g_MinZoom, g_MaxZoom);

					ImGui::PushID(2);
					ImGui::TextWrapped("");
					ImGui::SliderFloat("", &zoom, g_MinZoom, g_MaxZoom, "", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::TextWrapped("");
					ImGui::PopID();

					Window::setZoom((double)zoom, g_MinZoom, g_MaxZoom);

				}

				ImGui::PopItemWidth();

				ImGui::PopFont();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Lighting"))
			{
				ImGui::PushFont(g_FONT);

				ImGui::PushItemWidth(g_WidgetWidth * g_WINDOW.m_WIDTH);

				if (ImGui::TreeNodeEx("Light Intensity", ImGuiTreeNodeFlags_NoTreePushOnOpen))
				{

					ImGui::PushID(3);
					ImGui::TextWrapped("");
					ImGui::SliderFloat("", &g_Light.m_Intensity, 0.0f, 1.0f, "", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::TextWrapped("");
					ImGui::PopID();

				}

				if (ImGui::TreeNodeEx("Light Position", ImGuiTreeNodeFlags_NoTreePushOnOpen))
				{

					ImGui::PushID(4);

					if (ImGui::Button("Reset Position")) {
						g_Light.m_Angles = Vector(0.0f);
					}

					ImGui::PopID();

					ImGui::PushID(5);
					ImGui::SliderAngle("", &g_Light.m_Angles.m_Self[0], -180.0f, 180.0f, "x = %.1f", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::PopID();

					ImGui::PushID(6);
					ImGui::SliderAngle("", &g_Light.m_Angles.m_Self[1], -180.0f, 180.0f, "y = %.1f", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::PopID();

					ImGui::PushID(7);
					ImGui::SliderAngle("", &g_Light.m_Angles.m_Self[2], -180.0f, 180.0f, "z = %.1f", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::PopID();

					ImGui::TextWrapped("");

				}

				ImGui::PopItemWidth();
				ImGui::PopFont();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Options")) {

				ImGui::PushFont(g_FONT);

				if (ImGui::TreeNodeEx("Sensitivity", ImGuiTreeNodeFlags_NoTreePushOnOpen))
				{

					ImGui::PushID(8);
					ImGui::TextWrapped("");
					ImGui::SliderFloat("", &g_Sensitivity, 500.0f, 100.0f, "", ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_ClampOnInput);
					ImGui::TextWrapped("");
					ImGui::PopID();

				}

				ImGui::PushID(9);
				ImGui::Checkbox("Acceleration", &g_AccelerationFlag);
				ImGui::PopID();
				ImGui::PopFont();
				ImGui::TreePop();
			}

			ImGui::PopFont();

		}

		ImGui::End();

		//Static sizing for ImGui windows
		ImGui::SetNextWindowPos({(float)(g_WINDOW.m_WIDTH * g_Offset * 5.25), (float)(g_WINDOW.m_HEIGHT - g_WINDOW.m_HEIGHT / 4.0)});
		ImGui::SetNextWindowSize({ (float)(g_WINDOW.m_WIDTH - g_WINDOW.m_WIDTH * g_Offset / 5.25), (float)g_WINDOW.m_HEIGHT / 4});

		ImGui::PushFont(g_HEADERFONT);

		if (ImGui::Begin(g_Shape->m_Properties.m_Name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
		
			ImGui::Text("Surface Area:\n");

			ImGui::PopFont();
			ImGui::PushFont(g_FONT);

			ImGui::Text("%s", g_Shape->m_Properties.m_SurfaceArea);

			ImGui::PushFont(g_HEADERFONT);

			ImGui::Text("\nVolume:\n");

			ImGui::PopFont();
			ImGui::PushFont(g_FONT);

			ImGui::Text("%s", g_Shape->m_Properties.m_Volume);

			ImGui::PopFont();
		
		}

		ImGui::PopFont();
		ImGui::End();

	}

	void imGuiSwapShape(Shape& shape) {

		VertexArray::unbindArray();
		shape.m_VAO.bindArray();
		// Swap vertex arrays

		shape.m_Colour = g_Shape->m_Colour;
		shape.m_Matteness = g_Shape->m_Matteness;
		shape.m_Position = g_Shape->m_Position;
		g_Shape = &shape;
		// Swap properties

	}

private:

	unsigned int const g_FPS = 60;
	float g_Offset = 0.13;
	float g_WidgetWidth = 0.125;
	float const g_PI = 3.14159265358979323846264338327950288;
	float g_Sensitivity = 250;
	bool g_AccelerationFlag = true;
	float g_Acceleration = 10.0;
	int g_CameraPosition = 0;
	double g_MinZoom = g_PI / 4;
	double g_MaxZoom = g_PI / 2.5;
	// Constants

	Window g_WINDOW;
	Shader g_Shader;
	IO g_ImGui;
	ImGuiIO& g_IO;
	Cube g_Cube;
	Shape* g_Shape;
	Pyramid g_Pyramid;
	Cuboid g_Cuboid;
	TriPrism g_TriPrism;
	Renderer g_RENDERER;
	ImFont* g_FONT;
	ImFont* g_HEADERFONT;
	ImFont* g_TITLEFONT;
	LightSource g_Light;
	Camera g_Camera;
	Matrix g_Model;
	Matrix g_View;
	Matrix g_Projection;
	AxesX g_AxesX;
	AxesY g_AxesY;
	AxesZ g_AxesZ;
	GLFWimage g_ICON[1];
	// Other members

};

int main() {
	ShapeShifter PRG;
	PRG.Main();
}
// Entry point
