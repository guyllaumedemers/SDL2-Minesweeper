#pragma once
#include "ImGuiComponent.h"

namespace GraphicalToolset {
	class TopMenuBarImp {
	private:
		TopMenuBarImp(const TopMenuBarImp&) = delete;
		TopMenuBarImp(TopMenuBarImp&&) = delete;
	public:
		TopMenuBarImp();
		~TopMenuBarImp();
		void refresh();
	};
}