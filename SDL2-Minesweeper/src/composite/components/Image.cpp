#pragma once
#include "../../../headers/composite/components/Image.h"

namespace Toolset {
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