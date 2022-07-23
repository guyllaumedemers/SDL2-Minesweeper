#include "../../../headers/composite/components/Image.h"

namespace Toolset {
	void Image::refresh()
	{
		ImGui::Image(texture_id, texture_size);
	}
}