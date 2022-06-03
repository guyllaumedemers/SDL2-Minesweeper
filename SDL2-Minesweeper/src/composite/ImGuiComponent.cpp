#pragma once
#include "../../headers/composite/ImGuiComponent.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	ImGuiComponent::ImGuiComponent(const Rect& rect)
	{
#ifdef _DEBUG
		this->rect = DBG_NEW Rect(0, 0, 0, 0);
#else
		this->rect = new Rect(0, 0, 0, 0);
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	ImGuiComponent::~ImGuiComponent()
	{
		delete rect;
		rect = nullptr;
	}

	/// <summary>
	/// rect accessor
	/// </summary>
	const Rect& ImGuiComponent::getRect() const
	{
		return *rect;
	}
}