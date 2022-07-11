#pragma once
#include "../ImGuiSimpleComponent.h"

namespace Toolset {
	class Button : virtual public ImGuiSimpleComponent {
	protected:
		const char* name = nullptr;
		const char* event_key = nullptr;
	public:
		Button(const Button&) = delete;
		Button(Button&&) = delete;
		Button() = delete;
		Button(const Rect&, const char*, const char*);
		~Button() override;
		Button& operator=(const Button&) = delete;
		Button& operator=(Button&&) = delete;
		void refresh() override;
	};
}