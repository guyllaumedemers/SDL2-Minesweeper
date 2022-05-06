#pragma once
#include "ImGuiComponent.h"
#include "TopMenuBarImp.h"

namespace GraphicalToolset {
	class TopMenuBar : virtual public ImGuiComponent {
	private:
		TopMenuBarImp* imp = nullptr;
		TopMenuBar(const TopMenuBar&) = delete;
		TopMenuBar(TopMenuBar&&) = delete;
	public:
		TopMenuBar(TopMenuBarImp*);
		~TopMenuBar();
		void refresh() override;
	};
}