#pragma once
#include "../../headers/game/Screen.h"

namespace Toolset {
	int Screen::w = 640;
	int Screen::h = 480;

	void Screen::setScreenSize(const int& width, const int& height)
	{
		w = width;
		h = height;
	}
}