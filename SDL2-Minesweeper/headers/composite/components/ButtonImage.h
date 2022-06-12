#pragma once
#include "Button.h"
#include "Image.h"

namespace Toolset {
	class ButtonImage : virtual public Button {
	private:
		ButtonImage(const Button&) = delete;
		ButtonImage(Button&&) = delete;
		ButtonImage() = delete;
		Image* button_texture = nullptr;
	public:
		ButtonImage(const Rect&, const char*, const char*);
		~ButtonImage();
		void refresh() override;
	};
}