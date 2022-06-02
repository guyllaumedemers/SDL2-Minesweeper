#pragma once
#include "../ImGuiSimpleComponent.h"

using namespace std;
namespace Toolset {
	class Text : virtual public ImGuiSimpleComponent {
	private:
		Text(const Text&) = delete;
		Text(Text&&) = delete;
		Text() = delete;
	public:
		const char* text = nullptr;
		Text(const Rect&, const char*);
		~Text();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Text::Text(const Rect& rect, const char* text) : ImGuiSimpleComponent(rect), ImGuiComponent(rect)
	{
		this->text = text;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Text::~Text()
	{
	}
}