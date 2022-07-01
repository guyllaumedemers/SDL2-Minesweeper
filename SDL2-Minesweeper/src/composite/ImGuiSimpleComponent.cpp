#pragma once
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
	/// Get component width
	/// </summary>
	int ImGuiSimpleComponent::getComponentWidth()
	{
		return rect->w;
	}

	/// <summary>
	/// Get component height
	/// </summary>
	int ImGuiSimpleComponent::getComponentHeight()
	{
		return rect->h;
	}
}