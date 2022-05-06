#pragma once

namespace GraphicalToolset {
	class ImGuiComponent {
	private:
		ImGuiComponent() = delete;
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
	protected:
		virtual ~ImGuiComponent() {};
	public:
		virtual void refresh() = 0;
	};
}