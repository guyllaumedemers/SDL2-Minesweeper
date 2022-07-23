/*
 *	Benefits of explicitly defaulted and deleted functions
 *	https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-170
 *
 */

/// <summary>
/// base of composite pattern
/// </summary>
#ifndef INCLUDED_IMGUICOMPONENT
#define INCLUDED_IMGUICOMPONENT

#include "Rect.h"

namespace Toolset {
	class ImGuiComponent {
		Rect* rect = nullptr;
	protected:
		explicit ImGuiComponent(const Rect&);	// not sure I fully understand this one, Rider suggested it but the documentation explanation is very thin.
	public:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
		ImGuiComponent() = delete;
		virtual ~ImGuiComponent() = 0;
		ImGuiComponent& operator=(const ImGuiComponent&) = delete;
		ImGuiComponent& operator=(ImGuiComponent&&) = delete;
		const Rect& getRect() const				{ return *rect; }
		virtual int getComponentWidth()			{ return 0; }
		virtual int getComponentHeight()		{ return 0; }
		virtual void refresh() {}
	};

	inline ImGuiComponent::ImGuiComponent(const Rect& rect)
	{
		this->rect = new Rect(rect.x, rect.y, rect.w, rect.h);
	}

	inline ImGuiComponent::~ImGuiComponent()
	{
		delete rect;
		rect = nullptr;
	}
}
#endif