//
// Created by Maxime Blanc on 06/09/2021.
//

#include "Palette.h"

Jelly::Palette::Palette()=default;
Jelly::Palette::~Palette()=default;

std::tuple<GLfloat, GLfloat, GLfloat, GLfloat> Jelly::Palette::GLColor_A(int r, int g, int b, GLfloat a) {
	return std::make_tuple((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255, a);
}

std::tuple<GLfloat, GLfloat, GLfloat> Jelly::Palette::GLColor(int r, int g, int b) {
	return std::make_tuple((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
}

GLfloat Jelly::Palette::RGBToGL(int c) { return (GLfloat)c / 255; }