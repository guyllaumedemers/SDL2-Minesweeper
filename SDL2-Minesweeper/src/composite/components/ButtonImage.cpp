#pragma once
#include "../../../headers/composite/components/ButtonImage.h"
#include "../../../headers/EventHandler.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	ButtonImage::ButtonImage(const Rect& rect, const char* name, const char* event_key) : Button(rect, name, event_key), ImGuiSimpleComponent(rect), ImGuiComponent(rect)
	{
		this->button_texture = new Image(rect);
	}

	/// <summary>
	/// Destructor
	/// </summary>
	ButtonImage::~ButtonImage()
	{
		delete button_texture;
		button_texture = nullptr;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void ButtonImage::refresh()
	{
		if (ImGui::ImageButton(button_texture->getTextureId(), button_texture->getTextureSize())) { EventHandler::invoke(event_key, nullptr); }
	}
}