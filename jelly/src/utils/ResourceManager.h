//
// Created by Maxime Blanc on 07/09/2021.
//

#pragma once

#include "jelly/src/graphics/TextureCache.h"

namespace Jelly {
	class ResourceManager {
	public:
		static GLTexture GetTexture(const std::string &texturePath);

	private:
		static TextureCache _textureCache;
	};
}
