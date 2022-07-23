#include "../../../headers/composite/components/Image.h"

namespace Toolset {
	void Image::setImage(const ImTextureID& texture_id, const ImVec2& size)
	{
		this->texture_id = texture_id;
		this->texture_size = size;
	}
	
	void Image::refresh()
	{
		ImGui::Image(texture_id, texture_size);
	}
}