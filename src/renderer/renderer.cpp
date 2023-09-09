#include "renderer.h"

void Renderer::clearBuffer() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and reset the depth buffer
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background colour
}

void Renderer::drawElements(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) {

	ibo.bindBuffer(); // Bind index array
	shader.bindShader(); // Bind shader
	vao.bindArray(); // Bind vertex array

	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr); // Draw call

}
