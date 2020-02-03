#include "process_keyboard.h"
#include <iostream>


helper::input run() {
	if (GetAsyncKeyState(VK_UP) < 0) {
		std::cout << "up" << std:: endl;
		return helper::input::FORWARD;
	}

	if (GetAsyncKeyState(VK_DOWN) < 0) {
		std::cout << "up" << std::endl;
		return helper::input::BACKWARD;
	}
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		std::cout << "up" << std::endl;
		return helper::input::LEFT;
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		std::cout << "up" << std::endl;
		return helper::input::RIGHT;
	}

	if (GetAsyncKeyState(VK_ESCAPE) < 0) {
		std::cout << "ESC" << std::endl;
		return  helper::input::QUIT;
	}
	if (GetAsyncKeyState(VK_TAB) < 0) {
		std::cout << "TAB" << std::endl;
		return  helper::input::INFO;
	}
	if (GetAsyncKeyState(VK_RETURN) < 0) {
		std::cout << "RETURN" << std::endl;
		return  helper::input::ATTACK;
	}
	return  helper::input::NONE
}