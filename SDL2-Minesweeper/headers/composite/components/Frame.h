#pragma once
#include "../ImGuiComplexComponent.h"
#include "../Rect.h"

namespace Toolset {
	/// <summary>
	/// A frame represent the content area used by ImGui ui components, it can either be screen size or localized
	/// </summary>
	struct Frame : virtual public ImGuiComplexComponent {
	private:
		Frame(const& Frame) = delete;
		Frame(Frame&&) = delete;
		Frame() = delete;
	public:
		Rect rect;
		Frame(const Rect&);
		~Frame();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Frame::Frame(const Rect& rect)
	{
		/// <summary>
		/// A frame should by default have an Image or a Color assigned to it
		/// </summary>
		this->rect = rect;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Frame::~Frame()
	{
	}
}