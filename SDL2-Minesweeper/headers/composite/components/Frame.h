#pragma once
#include "../ImGuiComplexComponent.h"

namespace Toolset {
	/// <summary>
	/// A frame represent the content area used by ImGui ui components, it can either be screen size or localized
	/// </summary>
	class Frame : virtual public ImGuiComplexComponent {
	private:
		Frame(const Frame&) = delete;
		Frame(Frame&&) = delete;
		Frame() = delete;
	public:
		Frame(const Rect&);
		~Frame();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Frame::Frame(const Rect& rect) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Frame::~Frame()
	{
	}
}