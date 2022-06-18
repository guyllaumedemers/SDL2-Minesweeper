#pragma once
#include "../../headers/composite/ImGuiComponent.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	ImGuiComponent::ImGuiComponent(const Rect& rect)
	{
#ifdef _DEBUG
		this->rect = DBG_NEW Rect(rect.x, rect.y, rect.w, rect.h);
#else
		this->rect = new Rect(rect.x, rect.y, rect.w, rect.h);
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