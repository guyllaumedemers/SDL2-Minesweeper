#include "../../../headers/composite/components/Viewport.h"

namespace Toolset {
	void Viewport::setTextureViewport(const ImTextureID& texture_id, const ImGuiID& viewport_id)
	{
		ImGui::SetNextWindowPos(work_pos);
		ImGui::SetNextWindowSize(work_size);
		ImGui::SetNextWindowViewport(viewport_id);
		if (viewport_texture) viewport_texture->setImage(texture_id, work_size);
	}

	void Viewport::refresh()
	{
		if (viewport_texture) viewport_texture->refresh();
	}
}