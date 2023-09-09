#include "shader.h"

#include <utility>

Shader::Shader(std::string  VertexFP, std::string  FragmentFP) : m_VertexFP(std::move(VertexFP)), m_FragmentFP(std::move(FragmentFP)), m_ID(1) {

	unsigned int vertexID, fragmentID;

	try {

		std::ifstream vStream(m_VertexFP);
		std::stringstream vBuffer;
		vBuffer << vStream.rdbuf();
		std::string vertex = vBuffer.str();
		// Create a read stream from file to buffer

		std::ifstream fStream(m_FragmentFP);
		std::stringstream fBuffer;
		fBuffer << fStream.rdbuf();
		std::string fragment = fBuffer.str();
		// Create a read stream from file to buffer

		const char* p_Vertex = vertex.c_str();
		const char* p_Fragment = fragment.c_str();
		// Swap std::string for a const char pointer

		vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &p_Vertex, nullptr);
		glCompileShader(vertexID);
		checkErrors(vertexID, "VERTEX");
		// Attach and debug vertex shader

		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentID, 1, &p_Fragment, nullptr);
		glCompileShader(fragmentID);
		checkErrors(fragmentID, "FRAGMENT");
		// Attach and debug fragment shader
	}

	catch (std::ifstream::failure& e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	} // If file stream failed
	
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexID);
	glAttachShader(m_ID, fragmentID);
	glLinkProgram(m_ID);
	checkErrors(m_ID, "PROGRAM");
	// Attach shaders together to use in the program

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	// Free memory

	bindShader();
}

Shader::~Shader() {
	glDeleteProgram(m_ID);
}

void Shader::bindShader() const {
	glUseProgram(m_ID);
}

void Shader::unbindShader() {
	glUseProgram(0);
}

void Shader::setUniformVec3(const std::string& name, const Vector& vec) const {
	glUniform3fv(getUniformLocation(name), 1, vec.m_Self.data());
	// Send a 3-Vector to shader
}

void Shader::setUniformMat4(const std::string& name, const Matrix& mat) const {

	std::vector<float> builder;
	builder.reserve(mat.m_Self.size() * mat.m_Self[0].size());

	for (const auto& row : mat.m_Self) {
		builder.insert(builder.end(), row.begin(), row.end());
	}

	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, builder.data());
	// Send a 4-Matrix to shader
}

void Shader::setUniformf(const std::string& name, float f) const {
	glUniform1f(getUniformLocation(name), f);
	// Send a float to shader
}

int Shader::getUniformLocation(const std::string& name) const {
	return glGetUniformLocation(m_ID, name.c_str());
}

void Shader::checkErrors(unsigned int shader, const std::string& type){
	int success;
	char infoLog[1024]; // Array for error to be stored in
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success){
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}