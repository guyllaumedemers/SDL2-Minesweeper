#pragma once

namespace Toolset {
	/// <summary>
	/// Already public
	/// </summary>
	struct Screen {
		static int w;
		static int h;
		Screen(const Screen&) = delete;
		Screen(Screen&&) = delete;
		Screen() = delete;
		~Screen() {};
		Screen& operator=(const Screen&) = delete;
		Screen& operator=(Screen&&) = delete;
		static void setScreenSize(const int&, const int&);
	};

	int Screen::w = 640;
	int Screen::h = 480;

	void Screen::setScreenSize(const int& width, const int& height)
	{
		w = width;
		h = height;
	}
}