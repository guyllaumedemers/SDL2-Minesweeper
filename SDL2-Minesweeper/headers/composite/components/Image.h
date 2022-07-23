
#ifndef INCLUDED_IMAGE
#define INCLUDED_IMAGE

#include "../ImGuiSimpleComponent.h"
#include <imgui.h>

namespace Toolset {
	class Image final : virtual public ImGuiSimpleComponent {
		ImTextureID texture_id;
		ImVec2 texture_size;
	public:
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image() = delete;
		explicit Image(const Rect&);
		~Image() override;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) = delete;
		void setImage(const ImTextureID&, const ImVec2&);
		const ImTextureID& getTextureId() const	{ return texture_id; }
		const ImVec2& getTextureSize() const	{ return texture_size; }
		void refresh() override;
	};

	inline Image::Image(const Rect& rect) : ImGuiSimpleComponent(rect), ImGuiComponent(rect),
		texture_id(ImTextureID()),
		texture_size(ImVec2(0, 0))
	{}

	inline Image::~Image()
	{}
}
#endif