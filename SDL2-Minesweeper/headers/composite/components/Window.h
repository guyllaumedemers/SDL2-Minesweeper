#pragma once
#include "../ImGuiComplexComponent.h"
#include "Style.h"

namespace Toolset {
	class Window : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
		bool p_open = false;
		Style* window_style = nullptr;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window() = delete;
	public:
		Window(const Rect& rect, const char* name, Style*);
		~Window();
		void refresh() override;
	};
}