#pragma once
#include "../../../headers/composite/components/Frame.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Frame::Frame(const Rect& rect) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Frame::~Frame()
	{
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Frame::refresh()
	{
		//Do Something
	}
}