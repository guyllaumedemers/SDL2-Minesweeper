#include "../../../headers/composite/components/Canvas.h"

namespace Toolset {
	void Canvas::refresh()
	{
		if (canvas_viewport) canvas_viewport->refresh();
		ImGuiComplexComponent::refresh();
	}
}