#include "../../headers/composite/ImGuiComplexComponent.h"

namespace Toolset {
	void ImGuiComplexComponent::add(ImGuiComponent* component)
	{
		components.push_back(component);
	}

	void ImGuiComplexComponent::remove(ImGuiComponent* component)
	{
		auto it = find(components.begin(), components.end(), component);
		if (it != components.end()) components.erase(it);
	}

	void ImGuiComplexComponent::refresh()
	{
		for (const auto& it : components) it->refresh();
	}

	float ImGuiComplexComponent::getComponentWidth()
	{
		float result = 0;
		for (const auto& it : components) result += it->getRect().w;
		return result;
	}

	float ImGuiComplexComponent::getComponentHeight()
	{
		float result = 0;
		for (const auto& it : components) result += it->getRect().h;
		return result;
	}
}