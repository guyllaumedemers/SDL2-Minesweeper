
#ifndef INCLUDED_IMGUISIMPLECOMPONENT
#define INCLUDED_IMGUISIMPLECOMPONENT

#include "ImGuiComponent.h"

namespace Toolset {
	class ImGuiSimpleComponent : virtual public ImGuiComponent {
	protected:
		ImGuiSimpleComponent(const Rect&);
	public:
		ImGuiSimpleComponent(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent(ImGuiSimpleComponent&&) = delete;
		ImGuiSimpleComponent() = delete;
		~ImGuiSimpleComponent() override = default;
		ImGuiSimpleComponent& operator=(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent& operator=(ImGuiSimpleComponent&&) = delete;
		int getComponentWidth() override	{ return getRect().w; }
		int getComponentHeight() override	{ return getRect().h; }
		void refresh() override {}
	};
	
	inline ImGuiSimpleComponent::ImGuiSimpleComponent(const Rect& rect) : ImGuiComponent(rect)
	{}
}
#endif