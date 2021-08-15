#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.hpp"

Shader::Shader(const char* v_path, const char* f_path) {
	// 1. Retrieve vertex and fragment source code.
	std::string v_code;
    std::string f_code;
    std::ifstream v_file;
    std::ifstream f_file;

	// Ensure ifstream objects can throw exceptions
	v_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		v_file.open(v_path);
		f_file.open(f_path);
		std::stringstream v_stream, f_stream;

		v_stream << v_file.rdbuf();
		f_stream << f_file.rdbuf();
		v_file.close();
		f_file.close();

		v_code = v_stream.str();
		f_code = f_stream.str();
	}
	catch(std::ifstream::failure e) {
		fprintf(stderr, "Error, shader file not successfully read\n");
	}

	const char* v_shader_code = v_code.c_str();
	const char* f_shader_code = f_code.c_str();

	// 2. Compile the shaders
	unsigned int vertex, fragment;
	int success;
	char log[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &v_shader_code, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		fprintf(stderr, "Vertex shader compilation failed\n%s\n", log);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &f_shader_code, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragment, 512, NULL, log);
		fprintf(stderr, "Fragment shader compilation failed\n%s\n", log);
	}

	// Shader program
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(id, 512, NULL, log);
		fprintf(stderr, "Shader program linking failed\n%s\n", log);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec4(const std::string &name, glm::vec4 value) const {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setMat4(const std::string &name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}