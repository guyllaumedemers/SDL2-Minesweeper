#pragma once
#include "SDLHandler.h"

namespace Minesweeper {
	class GameManager {
	private:
		static SDLHandler* context;
		static bool isRunning;
		static void init();
		static void run();
		static void destroy();
	public:
		static int execute();
		static void exit();
	};
}