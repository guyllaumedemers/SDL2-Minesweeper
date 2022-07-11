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
	public:
		Style(const Style&) = delete;
		Style(Style&&) = delete;
		Style() = delete;
		Style(const ImGuiWindowFlags&, const bool&, const bool&);
		~Style();
		Style& operator=(const Style&) = delete;
		Style& operator=(Style&&) = delete;
		void add(const ImGuiWindowFlags&);
		void remove(const ImGuiWindowFlags&);
		bool getfullscreen();
		bool getpadding();
		void push(const ImGuiStyleVar&, const float&);
		void push(const ImGuiStyleVar&, const ImVec2&);
		void pop(const int& = 1);
		const ImGuiWindowFlags& getwindowFlags() const;
	};
}