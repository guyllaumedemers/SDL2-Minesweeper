
#ifndef INCLUDED_IMGUISIMPLECOMPONENT
#define INCLUDED_IMGUISIMPLECOMPONENT

#include "ImGuiComponent.h"

namespace Toolset {
	class ImGuiSimpleComponent : virtual public ImGuiComponent {
	protected:
		explicit ImGuiSimpleComponent(const Rect&);
	public:
		ImGuiSimpleComponent(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent(ImGuiSimpleComponent&&) = delete;
		ImGuiSimpleComponent() = delete;
		~ImGuiSimpleComponent() override;
		ImGuiSimpleComponent& operator=(const ImGuiSimpleComponent&) = delete;
		ImGuiSimpleComponent& operator=(ImGuiSimpleComponent&&) = delete;
		int getComponentWidth() override	{ return getRect().w; }
		int getComponentHeight() override	{ return getRect().h; }
	};
	
	inline ImGuiSimpleComponent::ImGuiSimpleComponent(const Rect& rect) : ImGuiComponent(rect)
	{}

	inline ImGuiSimpleComponent::~ImGuiSimpleComponent()
	{}
}
#endif