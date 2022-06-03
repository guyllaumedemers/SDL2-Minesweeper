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
}