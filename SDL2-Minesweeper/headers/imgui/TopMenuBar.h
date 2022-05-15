#pragma once
#include "ImGuiComponent.h"
#include "TopMenuBarImp.h"
#include "../EventHandler.h"
#include <vector>

using namespace Toolset;
using namespace std;
namespace GraphicalToolset {
	class TopMenuBar : virtual public ImGuiComponent {
	private:
		TopMenuBarImp* imp = nullptr;
		vector<EventHandler*> events;
		TopMenuBar(const TopMenuBar&) = delete;
		TopMenuBar(TopMenuBar&&) = delete;
		void destroy();
	public:
		TopMenuBar(TopMenuBarImp*);
		~TopMenuBar();
		void refresh() override;
	};
}