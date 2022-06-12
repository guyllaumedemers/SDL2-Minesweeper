#pragma once
#include "../ImGuiComplexComponent.h"
#include "Viewport.h"
#include "Style.h"
#include "Canvas.h"

namespace Toolset {
	class Window : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
		bool p_open = false;
		Style* window_style = nullptr;
		Canvas* window_canvas = nullptr;
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