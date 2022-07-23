
#ifndef INCLUDED_SCREEN
#define INCLUDED_SCREEN

namespace Toolset {
	struct Screen {
		static inline int w = 640;
		static inline int h = 480;
		Screen(const Screen&) = delete;
		Screen(Screen&&) = delete;
		Screen() = delete;
		~Screen() = delete;
		Screen& operator=(const Screen&) = delete;
		Screen& operator=(Screen&&) = delete;
		static void setScreenSize(const int&, const int&);
	};

	inline void Screen::setScreenSize(const int& width, const int& height)
	{
		w = width;
		h = height;
	}
}
#endif