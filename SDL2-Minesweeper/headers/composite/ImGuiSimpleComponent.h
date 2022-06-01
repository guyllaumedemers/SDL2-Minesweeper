#pragma once
#include "ImGuiComponent.h"

namespace Toolset {
	class ImGuiSimpleComponent : virtual public ImGuiComponent {
	private:
		ImGuiSimpleComponent(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent(ImGuiSimpleComponent&&) = delete;
		ImGuiSimpleComponent() = delete;
	protected:
		ImGuiSimpleComponent(Rect& rect) : ImGuiComponent(rect) {};
	public:
		virtual ~ImGuiSimpleComponent() = 0 {};
		int getcomponentHeight() override;
	};

	int ImGuiSimpleComponent::getcomponentHeight()
	{
		return rect.h;
	}
}