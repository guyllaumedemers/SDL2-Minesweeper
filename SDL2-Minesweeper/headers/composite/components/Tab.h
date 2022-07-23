
#ifndef INCLUDED_TAB
#define INCLUDED_TAB

#include "../ImGuiComplexComponent.h"

namespace Toolset {
	class Tab final : virtual public ImGuiComplexComponent {
		const char* name = nullptr;
	public:
		Tab(const Tab&) = delete;
		Tab(Tab&&) = delete;
		Tab() = delete;
		Tab(const Rect&, const char*);
		~Tab() override = default;
		Tab& operator=(const Tab&) = delete;
		Tab& operator=(Tab&&) = delete;
		void refresh() override;
	};

	inline Tab::Tab(const Rect& rect, const char* name) : ImGuiComplexComponent(rect), ImGuiComponent(rect),
		name(name)
	{}
}
#endif