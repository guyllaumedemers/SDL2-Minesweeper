#pragma once
#include "../../../headers/composite/components/Viewport.h"

#ifdef _DEBUG
#include "../../../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Viewport::Viewport(const Rect& rect) : work_pos(ImVec2(rect.x, rect.y)), work_size(ImVec2(rect.w, rect.h))
	{
#ifdef _DEBUG
		this->viewport_texture = DBG_NEW Image(rect);
#else
		this->viewport_texture = new Image(rect);
#endif
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
		if (viewport_texture) viewport_texture->setimage(texture_id, work_size);
	}

	/// <summary>
	/// Refresh image from the renderer context
	/// </summary>
	void Viewport::refresh()
	{
		if (viewport_texture) viewport_texture->refresh();
	}
}