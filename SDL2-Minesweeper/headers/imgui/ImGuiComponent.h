#pragma once

namespace GraphicalToolset {
	class ImGuiComponent {
	private:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
	protected:
		ImGuiComponent() = default;
	public:
		virtual ~ImGuiComponent() = 0 {};
		virtual void refresh() = 0;
	};
}