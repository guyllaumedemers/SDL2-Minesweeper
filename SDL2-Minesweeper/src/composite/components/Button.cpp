#pragma once
#include "../../../headers/composite/components/Button.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Button::Button(const Rect& rect) : ImGuiSimpleComponent(rect), ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Button::~Button()
	{
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Button::refresh()
	{
	}
}