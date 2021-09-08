//
// Created by Maxime Blanc on 05/09/2021.
//

#include "Engine.h"
#include <fmt/core.h>
#include <jelly/src/utils/Logger.h>

Engine::Engine() : _gameState(GameState::PLAY),
                   _screenWidth(1024),
                   _screenHeight(768),
                   _time(0),
                   _maxFPS(60.0f){};

Engine::~Engine() = default;

void Engine::_init() {


	_window.create("jelly Engine", _screenWidth, _screenHeight, 0);

	_initShaders();
}

void Engine::_initShaders() {
	_shaderProgram.compileShaders("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
	_shaderProgram.addAttribute("position");
	_shaderProgram.addAttribute("color");
	_shaderProgram.addAttribute("uv");
	_shaderProgram.linkShaders();

	Jelly::Logger::Warn("Shaders initialized ✓", false);
}

void Engine::run() {
	_init();

	_sprites.push_back(new Jelly::Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "textures/Celestial_Beatrix.png");
	_sprites.push_back(new Jelly::Sprite());
	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "textures/Celestial_Beatrix.png");
	_sprites.push_back(new Jelly::Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "textures/Boss_Feral_Kitsune.png");
	_sprites.push_back(new Jelly::Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "textures/Boss_Feral_Kitsune.png");

	_update();
}

void Engine::_update() {
	while (_gameState != GameState::EXIT) {
		// Used for frameTime measuring
		float startTicks = SDL_GetTicks();

		_processInput();
		_time += 0.1;
		_draw();
		_calculateFPS();
		_printFPS();

		float frameTicks = SDL_GetTicks() - startTicks;
		// Limit FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
	}

	Jelly::Logger::ClearLogs();
}

void Engine::_draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _shaderProgram.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _shaderProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	for (auto &sprite : _sprites) {
		sprite->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	_shaderProgram.drop();

	_window.swapBuffer();
}

void Engine::_processInput() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void Engine::_calculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	previousTicks = currentTicks;

	int count;

	currentFrame++;

	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	} else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0.0f;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	} else {
		_fps = 60.0f;
	}
}

void Engine::_printFPS() {
	static int frameCounter = 0;
	frameCounter++;

	if (frameCounter == 10) {
		Jelly::Logger::Trace(fmt::format("FPS: {}", _fps));
		frameCounter = 0;
	}
}
