#pragma once
#include "../ImGuiSimpleComponent.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	/// <summary>
	/// an image is self-explanatory
	/// </summary>
	class Image : virtual public ImGuiSimpleComponent {
	private:
		ImTextureID texture_id;
		ImVec2 size;
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image() = delete;
	public:
		Image(const Rect&);
		~Image();
		void setimage(const ImTextureID&, const ImVec2&);
		void refresh() override;
	};
}