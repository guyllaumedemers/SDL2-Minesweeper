
#ifndef INCLUDED_BUTTONIMAGE
#define INCLUDED_BUTTONIMAGE

#include "Button.h"
#include "Image.h"

namespace Toolset {
	class ButtonImage final : virtual public Button {
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

	inline ButtonImage::ButtonImage(const Rect& rect, const char* name, const char* event_key) : Button(rect, name, event_key), ImGuiSimpleComponent(rect), ImGuiComponent(rect),
		button_texture(new Image(rect))
	{}

	inline ButtonImage::~ButtonImage()
	{
		delete button_texture;
		button_texture = nullptr;
	}
}
#endif