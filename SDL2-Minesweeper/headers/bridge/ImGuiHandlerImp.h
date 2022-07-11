#pragma once
#include "../builder/IBuilder.h"

using namespace std;
namespace Toolset {
	/// <summary>
	/// Generic Type class using bridge pattern to pass args data to grahic APIs lib
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandlerImp {
	protected:
		ImGuiHandlerImp() = default;
	public:
		ImGuiHandlerImp(const ImGuiHandlerImp&) = delete;
		ImGuiHandlerImp(ImGuiHandlerImp&&) = delete;
		virtual ~ImGuiHandlerImp() = 0 {};
		ImGuiHandlerImp& operator=(const ImGuiHandlerImp&) = delete;
		ImGuiHandlerImp& operator=(ImGuiHandlerImp&&) = delete;
		virtual int pollEvents(void(*)(GraphicAPIsEvent&)) = 0;
		virtual void refresh(void(*)(GraphicAPIsRendering*)) = 0;
		virtual void draw(void(*)(GraphicAPIsRendering*)) = 0;
	};
}