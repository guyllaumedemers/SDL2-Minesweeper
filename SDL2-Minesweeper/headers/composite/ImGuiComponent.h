#pragma once
#include "Rect.h"

#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
	/// <summary>
	/// base of composite pattern
	/// </summary>
	class ImGuiComponent {
	private:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
		ImGuiComponent() = delete;
	protected:
		Rect* rect;
	public:
		ImGuiComponent(const Rect&);
		virtual ~ImGuiComponent() = 0;
		virtual int getComponentHeight() = 0;
		const Rect& getRect() const;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	ImGuiComponent::ImGuiComponent(const Rect& rect)
	{
#ifdef _DEBUG
		this->rect = DBG_NEW Rect(rect.x, rect.y, rect.w, rect.h);
#else
		this->rect = new Rect(rect.x, rect.y, rect.w, rect.h);
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	ImGuiComponent::~ImGuiComponent()
	{
		delete rect;
		rect = nullptr;
	}

	/// <summary>
	/// rect accessor
	/// </summary>
	const Rect& ImGuiComponent::getRect() const
	{
		return *rect;
	}
}