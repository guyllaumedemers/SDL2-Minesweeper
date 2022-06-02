#pragma once
#include "../ImGuiSimpleComponent.h"

namespace Toolset {
	/// <summary>
	/// an image is self-explanatory
	/// </summary>
	class Image : virtual public ImGuiSimpleComponent {
	private:
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image() = delete;
	public:
		Image(const Rect&);
		~Image();
		void refresh() override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Image::Image(const Rect& rect) : ImGuiSimpleComponent(rect), ImGuiComponent(rect)
	{
		/// <summary>
		/// Missing Color, or Texture
		/// </summary>
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Image::~Image()
	{
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Image::refresh()
	{
		//Do Something
	}
}