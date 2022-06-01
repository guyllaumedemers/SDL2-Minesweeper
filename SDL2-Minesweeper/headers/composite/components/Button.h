#pragma once
#include "../ImGuiComplexComponent.h"
#include "Text.h"
#include "Image.h"

namespace Toolset {
	struct Button : virtual public ImGuiComplexComponent {
	private:
		Button(const Button&) = delete;
		Button(Button&&) = delete;
		Button() = delete;
	public:
		Button(Rect&);
		Button(Rect&, Text&, Image&);
		~Button();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Button::Button(Rect& rect) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Constructor Alt
	/// </summary>
	Button::Button(Rect& rect, Text& text, Image& image) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
		add(&text);
		add(&image);
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Button::~Button()
	{
	}
}
