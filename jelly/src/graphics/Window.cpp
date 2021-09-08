//
// Created by Maxime Blanc on 07/09/2021.
//

#include "Window.h"
#include "jelly/src/utils/Logger.h"
#include <GL/glew.h>
#include <fmt/core.h>

Jelly::Window::Window() {}
Jelly::Window::~Window() {}

int Jelly::Window::create(const char *name, int width, int height, unsigned int currentFlags) {

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE) flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS) flags |= SDL_WINDOW_BORDERLESS;

	_sdlWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (_sdlWindow == nullptr) {
		Logger::Error("SDL window could not be created");
		SDL_Quit();
	}
	Logger::Trace("SDL window created...");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext ctx = SDL_GL_CreateContext(_sdlWindow);
	if (ctx == nullptr) {
		Logger::Error("SDL GL context could not be created");
		SDL_Quit();
	}
	Logger::Trace("SDL GL context created...");
	auto glVersion = glGetString(GL_VERSION);
	Logger::Trace(fmt::format("OpenGL version {}", glVersion));

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Logger::Error("Could not initialize GLEW");
		SDL_Quit();
	}
	Logger::Trace("GLEW initialized...");

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Enable VSYNC
	SDL_GL_SetSwapInterval(GL_TRUE);

	Logger::Warn("Jelly Engine initialized ✔", false);

	return 0;
}

void Jelly::Window::swapBuffer() {
	SDL_GL_SwapWindow(_sdlWindow);
}
