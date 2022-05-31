#pragma once
#include "../ImGuiSimpleComponent.h"
#include "Text.h"

namespace Toolset {
	struct Entry : virtual public ImGuiSimpleComponent {
	private:
		Entry(const& Entry) = delete;
		Entry(Entry&&) = delete;
		Entry() = delete;
	public:
		Text text;
		Entry(const Text&);
		~Entry();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	Entry::Entry(const Text& text)
	{
		this->text = text;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Entry::~Entry()
	{
	}
}