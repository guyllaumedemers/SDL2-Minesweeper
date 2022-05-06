#pragma once

namespace GraphicalToolset {
	class ImGuiComponent {
	private:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
	protected:
		ImGuiComponent() {};
		virtual ~ImGuiComponent() {};
	public:
		virtual void refresh() = 0;
	};
}