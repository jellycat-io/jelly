//
// Created by Maxime Blanc on 10/09/2021.
//

#include "InputManager.h"

Jelly::InputManager::InputManager() = default;
Jelly::InputManager::~InputManager() = default;

void Jelly::InputManager::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
}

void Jelly::InputManager::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
}

bool Jelly::InputManager::isKeyPressed(unsigned int keyID) {
	auto it = _keyMap.find(keyID);

	if (it != _keyMap.end()) {
		return it->second;
	}

	return false;
}
