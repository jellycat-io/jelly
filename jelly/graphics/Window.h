//
// Created by Maxime Blanc on 07/09/2021.
//

#pragma once

#include <SDL.h>

namespace Jelly {
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window {
	public:
		Window();
		~Window();

		int create(const char *name, int width, int height, unsigned int currentFlags);

		int getWidth() const { return _width; }
		int getHeight() const { return _height; }

		void swapBuffer();

	private:
		SDL_Window* _sdlWindow;
		int _width, _height;
	};
}
