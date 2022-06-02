#pragma once
#include "Level.h"
#include "Mode.h"
#include <SDL.h>

using namespace Minesweeper;
namespace Toolset {
	class LevelHandler {
	private:
		Level* level = nullptr;
		LevelHandler(const LevelHandler&) = delete;
		LevelHandler(LevelHandler&&) = delete;
		LevelHandler() = delete;
	public:
		LevelHandler(const Mode & = Mode::Easy);
		~LevelHandler();
		void update(const int&, const int&, const int&);
		void refresh(SDL_Renderer*, const int&, const int&);
		void draw(SDL_Renderer*);
		Level* getLevel();
	};
}