#include "../../../headers/composite/components/Tab.h"
#include <imgui.h>

namespace Toolset {
	void Tab::refresh()
	{
		if (name != nullptr && ImGui::BeginMenu(name)) {
			ImGuiComplexComponent::refresh();
			ImGui::EndMenu();
		}
	}
}