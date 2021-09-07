//
// Created by Maxime Blanc on 07/09/2021.
//

#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::GetTexture(const std::string &texturePath) {
	return _textureCache.getTexture(texturePath);
}
