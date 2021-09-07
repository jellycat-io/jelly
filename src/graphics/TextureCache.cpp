//
// Created by Maxime Blanc on 07/09/2021.
//

#include "TextureCache.h"
#include "../utils/ImageLoader.h"
#include "../utils/Logger.h"
#include <fmt/core.h>

TextureCache::TextureCache()=default;
TextureCache::~TextureCache()=default;

GLTexture TextureCache::getTexture(const std::string &texturePath) {
	// Lookup the texture
	auto mit = _textureMap.find(texturePath);

	// Check if the texture is cached
	if (mit == _textureMap.end()) {
		// Create a new texture...
		GLTexture newTexture = ImageLoader::LoadPNG(texturePath);
		// ... and cache it
		_textureMap.insert(std::make_pair(texturePath, newTexture));

		Logger::Trace(fmt::format("Cached new texture {}", texturePath));
		return newTexture;
	}


	Logger::Trace(fmt::format("Loaded cached texture {}", texturePath));
	return mit->second;
}
