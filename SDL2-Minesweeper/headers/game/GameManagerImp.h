#pragma once
#include "LevelHandler.h"
#include "Mode.h"
#include <SDL.h>

namespace Minesweeper {
	class GameManagerImp {
	private:
		LevelHandler* level_context = nullptr;
		GameManagerImp(const GameManagerImp&) = delete;
		GameManagerImp(GameManagerImp&&) = delete;
		void create(const Mode&);
		void destroy();
	public:
		GameManagerImp(const Mode&);
		~GameManagerImp();
		void processInputs();
		void refresh(SDL_Renderer*);
		void draw(SDL_Renderer*);
	};
}