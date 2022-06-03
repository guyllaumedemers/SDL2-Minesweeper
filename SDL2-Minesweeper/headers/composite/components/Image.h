#pragma once
#include "../ImGuiSimpleComponent.h"

namespace Toolset {
	/// <summary>
	/// an image is self-explanatory
	/// </summary>
	class Image : virtual public ImGuiSimpleComponent {
	private:
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image() = delete;
	public:
		Image(const Rect&);
		~Image();
		void refresh() override;
	};
}