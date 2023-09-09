#version 330 core

layout (location = 0) in vec3 a_Pos; // Input vertex position
layout (location = 1) in vec3 a_Normal; // Input normal of the plane that the vertex is part of

out vec3 Normal;
out vec3 FragPos;
out vec3 lightPos;
// Pass these to fragment shader
  
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float offset;
// Input uniforms, as specified in program

void main()
{
	gl_Position = projection * view * model * vec4(a_Pos, 1.0);
	// New position of vertex

	gl_Position.x += offset * gl_Position.w;
	// Position changed to account for position of ImGui windows

	FragPos = vec3(model * vec4(a_Pos, 1.0));

	Normal = mat3(transpose(inverse(model))) * a_Normal;
	// After applying matrix to positions, normals are not necessarily perpendicular to planes, so must adjust

}