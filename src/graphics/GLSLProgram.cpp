//
// Created by Maxime Blanc on 06/09/2021.
//

#include "GLSLProgram.h"
#include "../utils/IOManager.h"
#include "../utils/Logger.h"
#include <SDL.h>
#include <fmt/core.h>
#include <vector>

Jelly::GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {}
Jelly::GLSLProgram::~GLSLProgram()=default;

// Create shaders and compile them.
void Jelly::GLSLProgram::compileShaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		Logger::Error("Failed to create vertex shader");
		SDL_Quit();
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		Logger::Error("Failed to create fragment shader");
		SDL_Quit();
	}

	_compileShader(vertexShaderPath, _vertexShaderID);
	_compileShader(fragmentShaderPath, _fragmentShaderID);
}

// Link shaders into a program.
void Jelly::GLSLProgram::linkShaders() {
	// Attach shaders to te program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link the program
	glLinkProgram(_programID);

	// Get link status
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);

	if (!isLinked) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		Logger::Error(fmt::format("Program {} failed to link shaders", _programID));
		printf("%s\n", &(infoLog[0]));
		SDL_Quit();
	}

	// Always detach shaders after a successful ink
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void Jelly::GLSLProgram::addAttribute(const std::string &attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLint Jelly::GLSLProgram::getUniformLocation(const std::string &name) const {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	if (location == GL_INVALID_INDEX) {
		Logger::Error(fmt::format("Uniform {} not found in shader", name));
	}
	return location;
}

void Jelly::GLSLProgram::use() const {
	glUseProgram(_programID);

	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void Jelly::GLSLProgram::drop() const {
	glUseProgram(0);

	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

// Checks if a shader compiles correctly.
void Jelly::GLSLProgram::_checkShader(GLuint _shaderID) {
	GLint success = 0;
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL char
		std::vector<char> errorLog(maxLength);
		// Provide the info log
		glGetShaderInfoLog(_shaderID, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(_shaderID); // Don't leak the shader

		Logger::Error(fmt::format("Shader {} failed to compile", _shaderID));
		printf("%s\n", &(errorLog[0]));
		SDL_Quit();
	}
}

// Gets shader code from file and compiles it.
void Jelly::GLSLProgram::_compileShader(const std::string &filepath, GLuint shaderID) {
	// Convert shader file into a string
	std::string shaderData = IOManager::ReadFromFile(filepath);
	const char* shaderDataPtr = shaderData.c_str();

	// Indicate shader's source code
	glShaderSource(shaderID, 1, &shaderDataPtr, nullptr);

	// Compile the shader.
	glCompileShader(shaderID);

	// Check if shader compiles without error
	_checkShader(shaderID);
}
