//
// Created by Maxime Blanc on 08/09/2021.
//

#include "Jelly.h"
#include "jelly/src/utils/Logger.h"
#include <GL/glew.h>
#include <SDL.h>

int init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Jelly::Logger::Error("Error initializing SDL subsystems");
		return 1;
	}
	Jelly::Logger::Trace("SDL subsystems initialized...");

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return 0;
}
