//
// Created by Maxime Blanc on 06/09/2021.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void linkShaders();
	void addAttribute(const std::string &attributeName);
	GLint getUniformLocation(const std::string &name) const;
	void use() const;
	void drop() const;

private:
	void _checkShader(GLuint _shaderID);
	void _compileShader(const std::string &filepath, GLuint shaderID);

private:
	GLuint _numAttributes;
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};
