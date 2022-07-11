#pragma once
#include "../composite/ImGuiComponent.h"
#include "../composite/ImGuiSimpleComponent.h"
#include "../composite/ImGuiComplexComponent.h"
#include "../composite/components/Window.h"
#include "../composite/components/Canvas.h"
#include "../composite/components/Button.h"
#include "../composite/components/ButtonImage.h"
#include "../composite/components/Tab.h"
#include "../composite/components/Entry.h"

using namespace std;
namespace Toolset
{
	/// <summary>
	/// base class for builder pattern, use to work around generic implementation in its derived child
	/// </summary>
	class IBuilder {
	protected:
		IBuilder() = default;
	public:
		IBuilder(const IBuilder&) = delete;
		IBuilder(IBuilder&&) = delete;
		virtual ~IBuilder() = 0 { };
		IBuilder& operator=(const IBuilder&) = delete;
		IBuilder& operator=(IBuilder&&) = delete;
		virtual int getMaxWidth() = 0;
		virtual int getMaxHeight() = 0;
	};
}
