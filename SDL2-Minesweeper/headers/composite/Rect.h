#pragma once

namespace Toolset {
	/// <summary>
	/// default public, but code structure is consistent this way
	/// </summary>
	struct Rect {
		int x = 0, y = 0, w = 0, h = 0;
		Rect(const int& x, const int& y, const int& w, const int& h) : x(x), y(y), w(w), h(h) {};
		~Rect() {};
	private:
		/// <summary>
		/// deleting constructor in this specific case kinda makes it imposible to organize memory cluster in sequence since ImGuiComponents use pointers,
		/// this decrease the code efficiency by requiring non-successive memory address access but add flexibility during initialization stage
		/// </summary>
		Rect(const Rect&) = delete;
		Rect(Rect&&) = delete;
		Rect() = delete;
	};
}