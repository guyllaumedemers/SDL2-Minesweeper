#pragma once
#include "../ImGuiComplexComponent.h"
#include "Viewport.h"

namespace Toolset {
	/// <summary>
	/// A Canvas represent the content area used by ImGui ui components, it can either be screen size or localized
	/// </summary>
	class Canvas : virtual public ImGuiComplexComponent {
	private:
		Canvas(const Canvas&) = delete;
		Canvas(Canvas&&) = delete;
		Canvas() = delete;
		Viewport* canvas_viewport = nullptr;
	public:
		Canvas(const Rect&);
		~Canvas();
		Viewport* getCanvasViewport() const;
		void refresh() override;
	};
}