#pragma once

namespace Toolset {
	/// <summary>
	/// default public, but code structure is consistent this way
	/// </summary>
	struct Rect {
	private:
		Rect(const Rect&) = delete;
		Rect(Rect&&) = delete;
		Rect() = delete;
	public:
		int x = 0, y = 0, w = 0, h = 0;
		Rect(const int& x, const int& y, const int& w, const int& h) : x(x), y(y), w(w), h(h) {};
		~Rect() {};
	};
}