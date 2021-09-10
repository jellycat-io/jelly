//
// Created by Maxime Blanc on 08/09/2021.
//

#include "Camera2D.h"
#include <glm/ext.hpp>

Jelly::Camera2D::Camera2D() :
                       _screenWidth(0),
                       _screenHeight(0),
                       _needsMatrixUpdate(true),
                       _scale(1.0f),
                       _position(0.0f,0.0f),
                       _cameraMatrix(1.0f),
                       _orthoMatrix(1.0f) {}

Jelly::Camera2D::~Camera2D() {}

void Jelly::Camera2D::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float) _screenWidth, 0.0f, (float) _screenHeight);
}

void Jelly::Camera2D::update() {
	if (_needsMatrixUpdate) {
		glm::vec3 translate(-_position.x + (float)_screenWidth / 2, -_position.y + (float)_screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsMatrixUpdate = false;
	}
}
