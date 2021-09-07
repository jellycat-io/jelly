//
// Created by Maxime Blanc on 06/09/2021.
//

#pragma once

#include "GLTexture.h"
#include <GL/glew.h>
#include <string>

namespace Jelly {
	class Sprite {
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float w, float h, const std::string &texturePath);

		void draw();

	private:
		float _x{};
		float _y{};
		float _w{};
		float _h{};

		GLuint _vboID;
		GLuint _vaoID;

		GLTexture _texture{};
	};

}