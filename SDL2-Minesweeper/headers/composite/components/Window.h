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
	public:
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window() = delete;
		Window(const Rect& rect, const char* name, Style*);
		~Window() override;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		Canvas* getWindowCanvas() const;
		void refresh() override;
	};
}