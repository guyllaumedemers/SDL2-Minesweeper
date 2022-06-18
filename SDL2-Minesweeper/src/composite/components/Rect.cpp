#pragma once
#include "../../../headers/composite/Rect.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Rect::Rect(const int& x, const int& y, const int& w, const int& h) : x(x), y(y), w(w), h(h)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Rect::~Rect()
	{
	}
}