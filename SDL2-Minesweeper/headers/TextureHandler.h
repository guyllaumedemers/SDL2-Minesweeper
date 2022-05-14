#pragma once
#include <SDL.h>
#include <unordered_map>

using namespace std;
namespace Toolset {
	class TextureHandler {
	private:
		static unordered_map<string, SDL_Texture*> textures;
		TextureHandler() = delete;
		TextureHandler(const TextureHandler&) = delete;
		TextureHandler(TextureHandler&&) = delete;
		static SDL_Texture* loadtexture(SDL_Renderer*, const char*);
		static void add(const char* key, SDL_Texture*);
		static void remove(const char* key);
	public:
		static void init();
		static void load(SDL_Renderer*);
		static void destroy();
		static SDL_Texture* get(const char*);
	};
}