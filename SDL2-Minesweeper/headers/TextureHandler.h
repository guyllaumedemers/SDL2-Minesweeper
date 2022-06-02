#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

using namespace std;
namespace Toolset {
	class TextureHandler {
	private:
		static unordered_map<string, SDL_Texture*> textures;
		TextureHandler() = delete;
		TextureHandler(const TextureHandler&) = delete;
		TextureHandler(TextureHandler&&) = delete;
		static SDL_Texture* loadtexture(SDL_Renderer*, string);
		static void add(string key, SDL_Texture*);
		static void remove(string key);
	public:
		static void init();
		static void load(SDL_Renderer*);
		static void destroy();
		static SDL_Texture* get(string);
	};
}