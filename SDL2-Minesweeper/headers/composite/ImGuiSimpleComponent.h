#pragma once
#include "ImGuiComponent.h"

namespace Toolset {
	class ImGuiSimpleComponent : virtual public ImGuiComponent {
	public:
		ImGuiSimpleComponent(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent(ImGuiSimpleComponent&&) = delete;
		ImGuiSimpleComponent() = delete;
		ImGuiSimpleComponent(const Rect&);
		~ImGuiSimpleComponent() override;
		ImGuiSimpleComponent& operator=(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent& operator=(ImGuiSimpleComponent&&) = delete;
		void refresh() override;
		int getComponentWidth() override;
		int getComponentHeight() override;
	};
}