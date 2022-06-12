#pragma once
#include "../ImGuiSimpleComponent.h"

namespace Toolset {
	class Button : virtual public ImGuiSimpleComponent {
	private:
		Button(const Button&) = delete;
		Button(Button&&) = delete;
		Button() = delete;
	protected:
		const char* name = nullptr;
		const char* event_key = nullptr;
	public:
		Button(const Rect&, const char*, const char*);
		~Button();
		virtual void refresh() override;
	};
}