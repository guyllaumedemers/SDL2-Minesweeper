#pragma once
#include "../../headers/composite/ImGuiComponent.h"
#include "../../headers/composite/ImGuiComplexComponent.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	ImGuiComplexComponent::ImGuiComplexComponent(const Rect& rect) : ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	ImGuiComplexComponent::~ImGuiComplexComponent()
	{
		for (auto& it : components) {
			delete it;
			it = nullptr;
		}
		components.clear();
	}

	/// <summary>
	/// Adding component to pool
	/// </summary>
	void ImGuiComplexComponent::add(ImGuiComponent* component)
	{
		this->components.push_back(component);
	}

	/// <summary>
	/// Removing component to pool
	/// </summary>
	void ImGuiComplexComponent::remove(ImGuiComponent* component)
	{
		vector<ImGuiComponent*>::iterator it = find(components.begin(), components.end(), component);
		if (it != components.end()) components.erase(it);
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void ImGuiComplexComponent::refresh()
	{
		for (const auto& it : components) it->refresh();
	}

	/// <summary>
	/// Get total components height
	/// </summary>
	int ImGuiComplexComponent::getComponentHeight()
	{
		int result = 0;
		for (const auto& it : components) result += it->getRect().h;
		return result;
	}
}