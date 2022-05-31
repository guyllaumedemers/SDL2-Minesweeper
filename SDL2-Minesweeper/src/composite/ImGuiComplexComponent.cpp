#pragma once
#include "../../headers/composite/ImGuiComplexComponent.h"

namespace Toolset {
	ImGuiComplexComponent::ImGuiComplexComponent()
	{
	}

	ImGuiComplexComponent::~ImGuiComplexComponent()
	{
		for (auto& it : components) {
			delete it;
			it = nullptr;
		}
	}

	void ImGuiComplexComponent::add(ImGuiComponent* component)
	{
		this->components.push_back(component);
	}

	void ImGuiComplexComponent::remove(ImGuiComponent* component)
	{
		vector<ImGuiComponent*>::iterator it = find(components.begin(), components.end(), component);
		if (it != components.end()) components.erase(it);
	}

	int ImGuiComplexComponent::getcomponentHeight()
	{
		int result = 0;
		for (const auto& it : components) result += it->component_height;
		return result;
	}
}