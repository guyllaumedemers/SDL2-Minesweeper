#include "../../headers/game/Tile.h"
#include "../../headers/TextureHandler.h"
#include <string>

namespace Minesweeper {
	void Tile::refresh(SDL_Renderer* renderer)
	{
		static const std::string textures[5] = {
			"Covered",
			"Uncovered",
			"Flag",
			"Bomb",
			"Hit"
		};

		SDL_Texture* temp = nullptr;
		SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);

		if ((int)(bitmask & Tilebitmask::Covered)) {
			/// <summary>
			/// handling textures for flags
			/// </summary>
			/// <param name="renderer"></param>
			SDL_RenderCopy(renderer,
				Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(textures[0].c_str()),
				NULL,
				NULL
			);
			if ((int)(bitmask & Tilebitmask::Flag)) SDL_RenderCopy(renderer,
				temp = Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(textures[2].c_str()),
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
				Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(textures[1].c_str()),
				NULL,
				NULL
			);
			if ((int)(bitmask & Tilebitmask::Numbered)) SDL_RenderCopy(renderer,
				temp = Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(std::to_string(getValue()).c_str()),
				NULL,
				NULL
			);
			else if ((int)(bitmask & Tilebitmask::Bomb)) SDL_RenderCopy(renderer,
				temp = Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(textures[3].c_str()),
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
				Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(textures[4].c_str()),
				NULL,
				NULL
			);
			SDL_RenderCopy(renderer,
				temp = Toolset::TextureHandler<SDL_Renderer, SDL_Texture>::get(textures[3].c_str()),
				NULL,
				NULL
			);
		}
		temp = nullptr;
	}
}