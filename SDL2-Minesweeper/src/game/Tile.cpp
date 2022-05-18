#pragma once
#include "../../headers/game/Tile.h"
#include "../../headers/TextureHandler.h"

using namespace Toolset;
namespace Minesweeper {
	const int Tile::size = 20;
	const string Tile::textures[5] = { "Covered", "Uncovered", "Flag", "Bomb", "Hit" };

	Tile::Tile() : bitmask(Tilebitmask::Covered), value(0) { }
	Tile::~Tile() {}

	void Tile::add(const Tilebitmask& value)
	{
		bitmask |= value;
	}

	void Tile::remove(const Tilebitmask& value)
	{
		bitmask &= ~value;
	}

	void Tile::refresh(SDL_Renderer* renderer)
	{
		SDL_Texture* temp = nullptr;
		SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);
		if ((bitmask & Tilebitmask::Covered) == Tilebitmask::Covered) {
			SDL_RenderCopy(renderer, TextureHandler::get(textures[0].c_str()), NULL, NULL);
			if ((bitmask & Tilebitmask::Flag) == Tilebitmask::Flag) SDL_RenderCopy(renderer, temp = TextureHandler::get(textures[2].c_str()), NULL, NULL);
		}
		else if ((bitmask & Tilebitmask::Uncovered) == Tilebitmask::Uncovered) {
			SDL_RenderCopy(renderer, TextureHandler::get(textures[1].c_str()), NULL, NULL);
			if ((bitmask & Tilebitmask::Numbered) == Tilebitmask::Numbered) SDL_RenderCopy(renderer, temp = TextureHandler::get(to_string(getValue()).c_str()), NULL, NULL);
		}
		else {
			SDL_RenderCopy(renderer, TextureHandler::get(textures[4].c_str()), NULL, NULL);				// Hit
			SDL_RenderCopy(renderer, temp = TextureHandler::get(textures[3].c_str()), NULL, NULL);		// Bomb
		}
		temp = nullptr;
	}

	const Tilebitmask& Tile::getmask() const
	{
		return bitmask;
	}

	int Tile::getValue()
	{
		return 0;
	}

	void Tile::setValue(const int& value)
	{
		this->value = value;
	}
}