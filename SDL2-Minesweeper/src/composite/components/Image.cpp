#pragma once
#pragma once
#include "../../../headers/composite/components/Image.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Image::Image(const Rect& rect) : ImGuiSimpleComponent(rect), ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Image::~Image()
	{
	}

	/// <summary>
	/// set image info
	/// </summary>
	void Image::setimage(const ImTextureID& texture_id, const ImVec2& size)
	{
		this->texture_id = texture_id;
		this->size = size;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Image::refresh()
	{
		ImGui::Image(texture_id, size);
	}
}