#pragma once
#include "LevelHandler.h"
#include "Mode.h"

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
		void refresh();
		void draw();
	};
}