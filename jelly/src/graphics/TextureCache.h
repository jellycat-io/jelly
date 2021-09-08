//
// Created by Maxime Blanc on 07/09/2021.
//

#pragma once

#include "GLTexture.h"
#include <map>
#include <string>

namespace Jelly {
	class TextureCache {
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(const std::string &texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
