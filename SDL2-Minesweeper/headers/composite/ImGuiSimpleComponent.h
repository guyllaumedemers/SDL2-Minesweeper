#pragma once
#include "ImGuiComponent.h"

namespace Toolset {
	class ImGuiSimpleComponent : virtual public ImGuiComponent {
	private:
		ImGuiSimpleComponent(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent(ImGuiSimpleComponent&&) = delete;
		ImGuiSimpleComponent() = delete;
	public:
		ImGuiSimpleComponent(const Rect&);
		~ImGuiSimpleComponent();
		virtual void refresh() = 0;
		int getComponentHeight() override;
	};

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