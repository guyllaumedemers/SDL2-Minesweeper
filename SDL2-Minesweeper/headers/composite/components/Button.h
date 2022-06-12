#pragma once
#include "../ImGuiSimpleComponent.h"
#include "Image.h"

namespace Toolset {
	class Button : virtual public ImGuiSimpleComponent {
	private:
		Button(const Button&) = delete;
		Button(Button&&) = delete;
		Button() = delete;
		Image* button_texture = nullptr;
	public:
		Button(const Rect&);
		~Button();
		void refresh() override;
	};
}