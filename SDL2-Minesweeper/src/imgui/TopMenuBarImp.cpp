#include "../../headers/imgui/TopMenuBarImp.h"
#include <imgui_single_file.h>

namespace GraphicalToolset {
	TopMenuBarImp::TopMenuBarImp() {}
	TopMenuBarImp::~TopMenuBarImp() {}

	void TopMenuBarImp::refresh()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::BeginMenu("Mode")) {
				if (ImGui::MenuItem("Easy")) {}
				if (ImGui::MenuItem("Medium")) {}
				if (ImGui::MenuItem("Hard")) {}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Clear")) { /*Clear the Current Game State*/ }
			if (ImGui::MenuItem("Exit")) { /* Exit Game*/ }
			ImGui::EndMainMenuBar();
		}
	}
}
