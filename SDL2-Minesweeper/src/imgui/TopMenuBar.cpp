#include "../../headers/imgui/TopMenuBar.h"

namespace GraphicalToolset {
	TopMenuBar::TopMenuBar(TopMenuBarImp* imp) : imp(imp) {}
	TopMenuBar::~TopMenuBar() { destroy(); }

	void TopMenuBar::refresh()
	{
		imp->refresh();
	}

	void TopMenuBar::destroy()
	{
		delete imp;
		imp = nullptr;
	}
}
