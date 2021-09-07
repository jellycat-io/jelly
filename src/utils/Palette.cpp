//
// Created by Maxime Blanc on 06/09/2021.
//

#include "Palette.h"

Palette::Palette()=default;
Palette::~Palette()=default;

std::tuple<GLfloat, GLfloat, GLfloat, GLfloat> Palette::GLColor_A(int r, int g, int b, GLfloat a) {
	return std::make_tuple((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255, a);
}

std::tuple<GLfloat, GLfloat, GLfloat> Palette::GLColor(int r, int g, int b) {
	return std::make_tuple((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
}

GLfloat Palette::RGBToGL(int c) { return (GLfloat)c / 255; }