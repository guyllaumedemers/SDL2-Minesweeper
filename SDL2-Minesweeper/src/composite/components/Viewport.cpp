#pragma once
#include "../../../headers/composite/components/Viewport.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Viewport::Viewport(const ImVec2& work_pos, const ImVec2& work_size, const ImGuiID& work_id) : work_pos(work_pos), work_size(work_size), work_id(work_id)
	{
		ImGui::SetNextWindowPos(work_pos);
		ImGui::SetNextWindowSize(work_size);
		ImGui::SetNextWindowViewport(work_id);
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Viewport::~Viewport()
	{
	}
}