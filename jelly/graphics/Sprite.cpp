//
// Created by Maxime Blanc on 06/09/2021.
//

#include "Sprite.h"
#include "Vertex.h"
#include "jelly/utils/ResourceManager.h"

Jelly::Sprite::Sprite() : _vboID(0), _vaoID(0) {}

Jelly::Sprite::~Sprite() {
	if (_vboID != 0) glDeleteBuffers(1, &_vboID);
	if (_vaoID != 0) glDeleteVertexArrays(1, &_vaoID);
}

void Jelly::Sprite::init(float x, float y, float w, float h, const std::string &texturePath) {
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	_texture = ResourceManager::GetTexture(texturePath);

	// Generate vertex buffer
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];
	// First triangle
	vertexData[0].setPosition(_x + _w, _y + _h);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(_x, _y + _h);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(_x, _y);
	vertexData[2].setUV(0.0f, 0.0f);

	// Second triangle
	vertexData[3].setPosition(_x, _y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(_x + _w, _y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(_x + _w, _y + _h);
	vertexData[5].setUV(1.0f, 1.0f);

	for (auto & v : vertexData) {
		v.setColor(255, 255, 255);
	}



	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Jelly::Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	// Draw vertices to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
