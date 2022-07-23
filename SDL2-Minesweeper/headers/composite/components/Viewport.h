
#ifndef INCLUDED_VIEWPORT
#define INCLUDED_VIEWPORT

#include "Image.h"
#include <imgui.h>

namespace Toolset {
	class Viewport {
		ImVec2 work_pos;
		ImVec2 work_size;
		Image* viewport_texture = nullptr;
	public:
		Viewport(const Viewport&) = delete;
		Viewport(Viewport&&) = delete;
		Viewport() = delete;
		Viewport(const Rect&);
		~Viewport();
		Viewport& operator=(const Viewport&) = delete;
		Viewport& operator=(Viewport&&) = delete;
		void setTextureViewport(const ImTextureID&, const ImGuiID&);
		void refresh();
	};
	
	inline Viewport::Viewport(const Rect& rect) : work_pos(ImVec2(rect.x, rect.y)), work_size(ImVec2(rect.w, rect.h)),
		viewport_texture(new Image(rect))
	{}

	inline Viewport::~Viewport()
	{
		delete viewport_texture;
		viewport_texture = nullptr;
	}
	
}
#endif