//
// Created by Maxime Blanc on 06/09/2021.
//

#pragma once

#include <tuple>
#include <GL/glew.h>

class Palette {
public:
	Palette();
	~Palette();
	static std::tuple<GLfloat, GLfloat, GLfloat, GLfloat> GLColor_A(int r, int g, int b, GLfloat a);
	static std::tuple<GLfloat, GLfloat, GLfloat> GLColor(int r, int g, int b);
	static GLfloat RGBToGL(int c);
};
