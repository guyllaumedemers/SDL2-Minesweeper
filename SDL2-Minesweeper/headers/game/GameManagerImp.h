#pragma once
#include "LevelHandler.h"
#include "Mode.h"

#include <SDL.h>

namespace Toolset {
	class GameManagerImp {
	private:
		LevelHandler* level_context = nullptr;
		GameManagerImp(const GameManagerImp&) = delete;
		GameManagerImp(GameManagerImp&&) = delete;
		void create(const Mode&, void(*)(const int&, const int&));
		void destroy();
	public:
		GameManagerImp(const Mode&, void(*)(const int&, const int&));
		~GameManagerImp();
		void processInputs(const int&);
		void refresh(SDL_Renderer*, const int&, const int&);
		void draw(SDL_Renderer*);
	};
}