#pragma once
#include "../ImGuiComplexComponent.h"
#include "../Rect.h"
#include "Text.h"
#include "Image.h"

namespace Toolset {
	struct Button : virtual public ImGuiComplexComponent {
	private:
		Button(const& Button) = delete;
		Button(Button&&) = delete;
		Button() = delete;
	public:
		Rect rect;
		Text text;
		Image image;
		Button(const Rect&);
		Button(const Rect&, const Text&, const Image&);
		~Button();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Button::Button(const Rect& rect)
	{
		this->rect = rect;
	}

	/// <summary>
	/// Constructor Alt
	/// </summary>
	Button::Button(const Rect& rect, const Text& text, const Image& image)
	{
		this->rect = rect;
		this->text = text;
		this->image = image;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Button::~Button()
	{
	}
}