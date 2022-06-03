#pragma once
#include "../ImGuiComplexComponent.h"

namespace Toolset {
	class Tab : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
		Tab(const Tab&) = delete;
		Tab(Tab&&) = delete;
		Tab() = delete;
	public:
		Tab(const Rect&, const char*);
		~Tab();
		void refresh() override;
	};
}