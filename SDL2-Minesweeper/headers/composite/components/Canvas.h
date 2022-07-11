#pragma once
#include "../ImGuiComplexComponent.h"
#include "Viewport.h"

namespace Toolset {
	/// <summary>
	/// A Canvas represent the content area used by ImGui ui components, it can either be screen size or localized
	/// </summary>
	class Canvas final : virtual public ImGuiComplexComponent {
	private:
		Viewport* canvas_viewport = nullptr;
	public:
		Canvas(const Canvas&) = delete;
		Canvas(Canvas&&) = delete;
		Canvas() = delete;
		Canvas(const Rect&);
		~Canvas() override;
		Canvas& operator=(const Canvas&) = delete;
		Canvas& operator=(Canvas&&) = delete;
		Viewport* getCanvasViewport() const;
		void refresh() override;
	};
}