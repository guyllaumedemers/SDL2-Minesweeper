#pragma once
#include "Button.h"
#include "Image.h"

namespace Toolset {
	class ButtonImage final : virtual public Button {
	private:
		Image* button_texture = nullptr;
	public:
		ButtonImage(const Button&) = delete;
		ButtonImage(Button&&) = delete;
		ButtonImage() = delete;
		ButtonImage(const Rect&, const char*, const char*);
		~ButtonImage() override;
		ButtonImage& operator=(const ButtonImage&) = delete;
		ButtonImage& operator=(ButtonImage&&) = delete;
		void refresh() override;
	};
}