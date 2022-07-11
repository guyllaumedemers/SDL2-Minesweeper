#pragma once
#include "../../../headers/composite/components/Viewport.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Viewport::Viewport(const Rect& rect) : work_pos(ImVec2(rect.x, rect.y)), work_size(ImVec2(rect.w, rect.h))
	{
		this->viewport_texture = new Image(rect);
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Viewport::~Viewport()
	{
		delete viewport_texture;
		viewport_texture = nullptr;
	}

	void Viewport::setTextureViewport(const ImTextureID& texture_id, const ImGuiID& viewport_id)
	{
		ImGui::SetNextWindowPos(work_pos);
		ImGui::SetNextWindowSize(work_size);
		ImGui::SetNextWindowViewport(viewport_id);
		if (viewport_texture) viewport_texture->setImage(texture_id, work_size);
	}

	/// <summary>
	/// Refresh image from the renderer context
	/// </summary>
	void Viewport::refresh()
	{
		if (viewport_texture) viewport_texture->refresh();
	}
}