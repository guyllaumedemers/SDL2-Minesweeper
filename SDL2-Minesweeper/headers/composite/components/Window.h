
#ifndef INCLUDED_WINDOW
#define INCLUDED_WINDOW

#include "../ImGuiComplexComponent.h"
#include "Canvas.h"
#include "Style.h"

namespace Toolset {
	class Window : virtual public ImGuiComplexComponent {
		Canvas* window_canvas = nullptr;
		Style* window_style = nullptr;
		const char* name = "";
		bool p_open = false;
	public:
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window() = delete;
		Window(const Rect& rect, const char* name, Style*);
		~Window() override;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		Canvas& getWindowCanvas() const { return *window_canvas; }
		void refresh() override;
	};

	inline Window::Window(const Rect& rect, const char* name, Style* window_style) : ImGuiComplexComponent(rect), ImGuiComponent(rect),
		window_canvas(new Canvas(rect)),
		window_style(window_style),
		name(name),
		p_open(true)
	{}

	inline Window::~Window()
	{
		delete window_style;
		window_style = nullptr;
		delete window_canvas;
		window_canvas = nullptr;
	}
}
#endif