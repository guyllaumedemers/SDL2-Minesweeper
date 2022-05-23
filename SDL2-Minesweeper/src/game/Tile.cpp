#pragma once
#include "../../headers/game/Tile.h"
#include "../../headers/TextureHandler.h"

using namespace Toolset;
namespace Minesweeper {
	const int Tile::size = 20;
	const string Tile::textures[5] = { "Covered", "Uncovered", "Flag", "Bomb", "Hit" };

	Tile::Tile() : bitmask(Tilebitmask::Covered), value(0), index(-1) { }
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

		if ((int)(bitmask & Tilebitmask::Covered)) {
			/// <summary>
			/// handling textures for flags
			/// </summary>
			/// <param name="renderer"></param>
			SDL_RenderCopy(renderer,
				TextureHandler::get(textures[0].c_str()),
				NULL,
				NULL
			);
			if ((int)(bitmask & Tilebitmask::Flag)) SDL_RenderCopy(renderer,
				temp = TextureHandler::get(textures[2].c_str()),
				NULL,
				NULL
			);
		}
		else if ((int)(bitmask & Tilebitmask::Uncovered)) {
			/// <summary>
			/// handling textures for tile discovery
			/// </summary>
			/// <param name="renderer"></param>
			SDL_RenderCopy(renderer,
				TextureHandler::get(textures[1].c_str()),
				NULL,
				NULL
			);
			if ((int)(bitmask & Tilebitmask::Numbered)) SDL_RenderCopy(renderer,
				temp = TextureHandler::get(to_string(getValue()).c_str()),
				NULL,
				NULL
			);
		}
		else {
			/// <summary>
			/// handling textures onHit
			/// </summary>
			/// <param name="renderer"></param>
			if ((int)(bitmask & Tilebitmask::Hit)) SDL_RenderCopy(renderer,
				TextureHandler::get(textures[4].c_str()),
				NULL,
				NULL
			);
			SDL_RenderCopy(renderer,
				temp = TextureHandler::get(textures[3].c_str()),
				NULL,
				NULL
			);
		}
		temp = nullptr;
	}

	const Tilebitmask& Tile::getmask() const
	{
		return bitmask;
	}

	const int& Tile::getIndex() const
	{
		return index;
	}

	const int& Tile::getValue() const
	{
		return value;
	}

	void Tile::setIndex(const int& value)
	{
		this->index = value;
	}

	void Tile::setValue(const int& value)
	{
		this->value = value;
	}
}