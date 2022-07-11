#pragma once
#include "../ImGuiSimpleComponent.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	/// <summary>
	/// an image is self-explanatory
	/// </summary>
	class Image final : virtual public ImGuiSimpleComponent {
	private:
		ImTextureID texture_id = ImTextureID();
		ImVec2 size = ImVec2();
	public:
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image() = delete;
		Image(const Rect&);
		~Image() override;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) = delete;
		void setImage(const ImTextureID&, const ImVec2&);
		const ImTextureID& getTextureId() const;
		const ImVec2& getTextureSize() const;
		void refresh() override;
	};
}