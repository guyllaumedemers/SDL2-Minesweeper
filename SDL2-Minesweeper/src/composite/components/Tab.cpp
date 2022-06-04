#pragma once
#include "../../../headers/composite/components/Tab.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	/// <summary>
	/// Constructor overload
	/// </summary>
	Tab::Tab(const Rect& rect, const char* name) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
		this->name = name;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Tab::~Tab()
	{
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Tab::refresh()
	{
		if (ImGui::BeginMenu(name)) {
			ImGuiComplexComponent::refresh();
			ImGui::EndMenu();
		}
	}
}