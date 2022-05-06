#include "../../headers/imgui/TopMenuBar.h"

namespace GraphicalToolset {
	TopMenuBar::TopMenuBar(TopMenuBarImp* imp) : imp(imp) {}
	TopMenuBar::~TopMenuBar() {}

	void TopMenuBar::refresh()
	{
		imp->refresh();
	}
}
