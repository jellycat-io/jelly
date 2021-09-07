//
// Created by Maxime Blanc on 06/09/2021.
//

#pragma once

#include "../graphics/GLTexture.h"
#include <string>

class ImageLoader {
public:
	static GLTexture LoadPNG(const std::string &filepath);
};
