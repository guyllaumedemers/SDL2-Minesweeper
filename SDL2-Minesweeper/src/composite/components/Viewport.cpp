#pragma once
#include "../../../headers/composite/components/Viewport.h"

#ifdef _DEBUG
#include "../../../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Viewport::Viewport(const Rect& rect) : work_pos(ImVec2(rect.x, rect.y)), work_size(ImVec2(rect.w, rect.h)), texture_viewport(nullptr)
	{
#ifdef _DEBUG
		this->texture_viewport = DBG_NEW Image(rect);
#else
		this->texture_viewport = new Image(rect);
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Viewport::~Viewport()
	{
		delete texture_viewport;
		texture_viewport = nullptr;
	}

	void Viewport::setviewport(const ImTextureID& texture_id, const ImGuiID& viewport_id)
	{
		ImGui::SetNextWindowPos(work_pos);
		ImGui::SetNextWindowSize(work_size);
		ImGui::SetNextWindowViewport(viewport_id);
		texture_viewport->setimage(texture_id, work_size);
	}

	/// <summary>
	/// refresh image from the renderer context
	/// </summary>
	void Viewport::refresh()
	{
		texture_viewport->refresh();
	}
}