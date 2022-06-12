#pragma once
#include "../ImGuiComplexComponent.h"
#include "Canvas.h"
#include "Style.h"

namespace Toolset {
	class Window : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
		bool p_open = false;
		Canvas* window_canvas = nullptr;
		Style* window_style = nullptr;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window() = delete;
	public:
		Window(const Rect& rect, const char* name, Style*);
		~Window();
		Canvas* getWindowCanvas() const;
		void refresh() override;
	};
}