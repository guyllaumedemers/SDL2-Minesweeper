#pragma once
#include "../../headers/composite/ImGuiComponent.h"
#include "../../headers/composite/ImGuiSimpleComponent.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	ImGuiSimpleComponent::ImGuiSimpleComponent(const Rect& rect) : ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	ImGuiSimpleComponent::~ImGuiSimpleComponent()
	{
	}

	/// <summary>
	/// Get component height
	/// </summary>
	int ImGuiSimpleComponent::getComponentHeight()
	{
		return rect->h;
	}
}