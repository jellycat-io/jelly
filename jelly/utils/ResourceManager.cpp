//
// Created by Maxime Blanc on 07/09/2021.
//

#include "ResourceManager.h"

Jelly::TextureCache Jelly::ResourceManager::_textureCache;

Jelly::GLTexture Jelly::ResourceManager::GetTexture(const std::string &texturePath) {
	return _textureCache.getTexture(texturePath);
}
