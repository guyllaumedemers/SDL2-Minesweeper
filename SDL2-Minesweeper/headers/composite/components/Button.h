
#ifndef INCLUDED_BUTTON
#define INCLUDED_BUTTON

#include "../ImGuiSimpleComponent.h"

namespace Toolset {
	class Button : virtual public ImGuiSimpleComponent {
		const char* name = nullptr;
		const char* event_key = nullptr;
	public:
		Button(const Button&) = delete;
		Button(Button&&) = delete;
		Button() = delete;
		Button(const Rect&, const char*, const char*);
		~Button() override = default;
		Button& operator=(const Button&) = delete;
		Button& operator=(Button&&) = delete;
		const char* getName() const		{ return name; }
		const char* getEventKey() const	{ return event_key; }
		void refresh() override;
	};
	
	inline Button::Button(const Rect& rect, const char* name, const char* event_key) : ImGuiSimpleComponent(rect), ImGuiComponent(rect),
		name(name),
		event_key(event_key)
	{}
}
#endif