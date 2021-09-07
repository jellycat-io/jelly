//
// Created by Maxime Blanc on 07/09/2021.
//

#pragma once

#include "../graphics/TextureCache.h"

class ResourceManager {
public:
	static GLTexture GetTexture(const std::string &texturePath);

private:
	static TextureCache _textureCache;
};
