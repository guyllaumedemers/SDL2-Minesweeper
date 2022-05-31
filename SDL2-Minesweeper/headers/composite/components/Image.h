#pragma once
#include "../ImGuiSimpleComponent.h"
#include "../Rect.h"

namespace Toolset {
	/// <summary>
	/// an image is self-explanatory
	/// </summary>
	struct Image : virtual public ImGuiSimpleComponent {
	private:
		Image(const& Image) = delete;
		Image(Image&&) = delete;
		Image() = delete;
	public:
		Rect rect;
		Image(const Rect&);
		~Image();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Image::Image(const Rect& rect)
	{
		/// <summary>
		/// Missing texture assignment which needs to be generic so any graphic library can load them
		/// </summary>
		this->rect = rect;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Image::~Image()
	{
	}
}