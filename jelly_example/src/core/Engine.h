//
// Created by Maxime Blanc on 05/09/2021.
//

#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <jelly/src/graphics/Camera2D.h>
#include <jelly/src/graphics/GLSLProgram.h>
#include <jelly/src/graphics/Sprite.h>
#include <jelly/src/graphics/Window.h>
#include <vector>

enum class GameState {
	PLAY,
	EXIT
};

class Engine {
private:
	Jelly::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	std::vector<Jelly::Sprite *> _sprites;
	Jelly::GLSLProgram _shaderProgram{};
	float _time;
	float _maxFPS;
	float _fps{};
	float _frameTime{};
	Jelly::Camera2D _camera{};

public:
	Engine();
	~Engine();

	void run();

private:
	void _init();
	void _initShaders();
	void _update();
	void _draw();
	void _processInput();
	void _calculateFPS();
	void _printFPS();
};
