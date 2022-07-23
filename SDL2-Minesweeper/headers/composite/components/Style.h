
#ifndef INCLUDED_STYLE
#define INCLUDED_STYLE

#include <imgui.h>

namespace Toolset {
	class Style {
		ImGuiWindowFlags window_flags = -1;
		bool opt_fullscreen = false;
		bool opt_padding = false;
	public:
		Style(const Style&) = delete;
		Style(Style&&) = delete;
		Style() = delete;
		Style(const ImGuiWindowFlags&, const bool&, const bool&);
		~Style() = default;
		Style& operator=(const Style&) = delete;
		Style& operator=(Style&&) = delete;
		bool getFullscreen()	{ return opt_fullscreen; }
		bool getPadding()		{ return opt_padding; }
		const ImGuiWindowFlags& getWindowFlags() const { return window_flags; }
		void add(const ImGuiWindowFlags&);
		void remove(const ImGuiWindowFlags&);
		void push(const ImGuiStyleVar&, const float&);
		void push(const ImGuiStyleVar&, const ImVec2&);
		void pop(const int& = 1);
	};

	inline Style::Style(const ImGuiWindowFlags& window_flags, const bool& opt_fullscreen, const bool& opt_padding) :
		window_flags(window_flags),
		opt_fullscreen(opt_fullscreen),
		opt_padding(opt_padding)
	{}
}
#endif