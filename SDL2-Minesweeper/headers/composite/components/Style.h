#pragma once
#include <imgui.h>
#include <imgui_internal.h>

using namespace std;
namespace Toolset {
	class Style {
	private:
		ImGuiWindowFlags window_flags = -1;
		bool opt_fullscreen = false;
		bool opt_padding = false;
		Style(const Style&) = delete;
		Style(Style&&) = delete;
		Style() = delete;
	public:
		Style(const ImGuiWindowFlags&, const bool&, const bool&);
		~Style();
		void add(const ImGuiWindowFlags&);
		void remove(const ImGuiWindowFlags&);
		bool getfullscreen();
		bool getpadding();
		const ImGuiWindowFlags& getwindowFlags() const;
	};
}