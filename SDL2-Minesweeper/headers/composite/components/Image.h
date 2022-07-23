
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
		Image(const Rect&);
		~Image() override;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) = delete;
		const ImTextureID& getTextureId() const	{ return texture_id; }
		const ImVec2& getTextureSize() const	{ return texture_size; }
		void setImage(const ImTextureID& id, const ImVec2& size) { this->texture_id = id; this->texture_size = size; }
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