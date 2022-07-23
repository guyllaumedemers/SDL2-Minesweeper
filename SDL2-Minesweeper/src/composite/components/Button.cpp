#include "../../../headers/composite/components/Button.h"
#include "../../../headers/EventHandler.h"
#include <imgui.h>

namespace Toolset {
	void Button::refresh()
	{
		//TODO Finish implementation as EventHandler invoke with nullptr
		if (name != nullptr && ImGui::Button(name, ImVec2(getRect().x, getRect().y))) { EventHandler::invoke(event_key, nullptr); }
	}
}