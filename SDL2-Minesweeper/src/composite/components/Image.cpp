#pragma once
#include "../../../headers/composite/components/Image.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Image::Image(const Rect& rect) : ImGuiSimpleComponent(rect), ImGuiComponent(rect), texture_id(ImTextureID()), size(ImVec2(0, 0))
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
	void Image::setImage(const ImTextureID& texture_id, const ImVec2& size)
	{
		this->texture_id = texture_id;
		this->size = size;
	}

	/// <summary>
	/// get texture id
	/// </summary>
	const ImTextureID& Image::getTextureId() const
	{
		return texture_id;
	}

	/// <summary>
	/// get texture size
	/// </summary>
	const ImVec2& Image::getTextureSize() const
	{
		return size;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Image::refresh()
	{
		ImGui::Image(texture_id, size);
	}
}