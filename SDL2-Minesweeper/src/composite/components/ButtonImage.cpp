#include "../../../headers/composite/components/ButtonImage.h"
#include "../../../headers/EventHandler.h"

namespace Toolset {
	void ButtonImage::refresh()
	{
		//TODO Finish implementation as EventHandler invoke with nullptr
		if (ImGui::ImageButton(button_texture->getTextureId(), button_texture->getTextureSize())) { EventHandler::invoke(getEventKey(), nullptr); }
	}
}