#pragma once
#include "ImGuiComponent.h"

namespace Toolset {
	class ImGuiSimpleComponent : virtual public ImGuiComponent {
	private:
		ImGuiSimpleComponent(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent(ImGuiSimpleComponent&&) = delete;
	protected:
		ImGuiSimpleComponent() {};
	public:
		virtual ~ImGuiSimpleComponent() = 0 {};
		int getcomponentHeight() override;
	};

	int ImGuiSimpleComponent::getcomponentHeight()
	{
		return component_height;
	}
}