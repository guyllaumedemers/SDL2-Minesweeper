
#ifndef INCLUDED_CANVAS
#define INCLUDED_CANVAS

#include "../ImGuiComplexComponent.h"
#include "Viewport.h"

namespace Toolset {
	class Canvas final : virtual public ImGuiComplexComponent {
		Viewport* canvas_viewport = nullptr;
	public:
		Canvas(const Canvas&) = delete;
		Canvas(Canvas&&) = delete;
		Canvas() = delete;
		Canvas(const Rect&);
		~Canvas() override;
		Canvas& operator=(const Canvas&) = delete;
		Canvas& operator=(Canvas&&) = delete;
		Viewport& getCanvasViewport() const { return *canvas_viewport; }
		void refresh() override;
	};
	
	inline Canvas::Canvas(const Rect& rect) : ImGuiComplexComponent(rect), ImGuiComponent(rect),
		canvas_viewport(new Viewport(rect))
	{}

	inline Canvas::~Canvas()
	{
		delete canvas_viewport;
		canvas_viewport = nullptr;
	}
}
#endif