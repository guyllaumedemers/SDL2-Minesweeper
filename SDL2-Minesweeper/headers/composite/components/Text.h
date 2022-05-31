#pragma once
#include "../ImGuiSimpleComponent.h"

using namespace std;
namespace Toolset {
	struct Text : virtual public ImGuiSimpleComponent {
	private:
		Text(const& Text) = delete;
		Text(Text&&) = delete;
		Text() = delete;
	public:
		const char* text = nullptr;
		Text(const char*);
		~Text();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Text::Text(const char* text)
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