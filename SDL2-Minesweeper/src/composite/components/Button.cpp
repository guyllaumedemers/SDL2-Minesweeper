#pragma once
#include "../../../headers/composite/components/Button.h"
#include "../../../headers/EventHandler.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Button::Button(const Rect& rect, const char* name, const char* event_key) : ImGuiSimpleComponent(rect), ImGuiComponent(rect), name(name), event_key(event_key)
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
		if (ImGui::Button(name, ImVec2(rect->x, rect->y))) { EventHandler::invoke(event_key, nullptr); }
	}
}