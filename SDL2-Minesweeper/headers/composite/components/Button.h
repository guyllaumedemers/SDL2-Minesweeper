#pragma once
#include "../ImGuiComplexComponent.h"
#include "Text.h"
#include "Image.h"

namespace Toolset {
	/// <summary>
	/// The initializers where class-or-identifier names a virtual base class are ignored during construction of any class that is not the most derived class
	/// of the object that's being constructed. https://en.cppreference.com/w/cpp/language/constructor
	/// </summary>
	struct Button : virtual public ImGuiComplexComponent {
	private:
		Button(const Button&) = delete;
		Button(Button&&) = delete;
		Button() = delete;
	public:
		Button(const Rect&);
		Button(const Rect&, Text&, Image&);
		~Button();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Button::Button(const Rect& rect) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Constructor overload
	/// </summary>
	Button::Button(const Rect& rect, Text& text, Image& image) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
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
