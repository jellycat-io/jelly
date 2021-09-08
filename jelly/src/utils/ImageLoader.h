//
// Created by Maxime Blanc on 06/09/2021.
//

#pragma once

#include "jelly/src/graphics/GLTexture.h"
#include <string>

namespace Jelly {

	class ImageLoader {
	public:
		static GLTexture LoadPNG(const std::string &filepath);
	};

}
