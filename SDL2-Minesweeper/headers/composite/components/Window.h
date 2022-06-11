#pragma once
#include "../ImGuiComplexComponent.h"
#include "Viewport.h"
#include "Style.h"

namespace Toolset {
	class Window : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
		bool p_open = false;
		Style* window_style = nullptr;
		Viewport* window_viewport = nullptr;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window() = delete;
	public:
		Window(const Rect& rect, const char* name, Style*);
		~Window();
		Viewport* getWindowViewport() const;
		void refresh() override;
	};
}