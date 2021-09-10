//
// Created by Maxime Blanc on 10/09/2021.
//

#pragma once

#include <unordered_map>

namespace Jelly {
	class InputManager {
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);

	private:
		std::unordered_map<unsigned int, bool> _keyMap;
	};
}
