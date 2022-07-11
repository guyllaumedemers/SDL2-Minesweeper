#pragma once
#include "../ImGuiComplexComponent.h"

namespace Toolset {
	class Tab final : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
	public:
		Tab(const Tab&) = delete;
		Tab(Tab&&) = delete;
		Tab() = delete;
		Tab(const Rect&, const char*);
		~Tab() override;
		Tab& operator=(const Tab&) = delete;
		Tab& operator=(Tab&&) = delete;
		void refresh() override;
	};
}