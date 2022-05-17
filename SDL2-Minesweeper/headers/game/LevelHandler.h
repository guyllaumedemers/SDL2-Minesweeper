#pragma once
#include "Level.h"
#include "Mode.h"
#include <SDL.h>

namespace Minesweeper {
	class LevelHandler {
	private:
		Level* level = nullptr;
		LevelHandler() = delete;
		LevelHandler(const LevelHandler&) = delete;
		LevelHandler(LevelHandler&&) = delete;
		void create(const Mode&);
		void destroy();
	public:
		LevelHandler(const Mode & = Mode::Easy);
		~LevelHandler();
		void update(const int&, const int&);
		void refresh(SDL_Renderer*);
		void draw(SDL_Renderer*);
	};
}