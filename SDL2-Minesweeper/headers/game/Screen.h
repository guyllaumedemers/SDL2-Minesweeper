#pragma once

namespace Toolset {
	/// <summary>
	/// Already public
	/// </summary>
	struct Screen {
	public:
		static int w;
		static int h;
		static void setScreenSize(const int&, const int&);
	};
}