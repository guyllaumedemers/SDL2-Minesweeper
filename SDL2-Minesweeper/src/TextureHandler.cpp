#pragma once
#include "../headers/TextureHandler.h"
#include "../headers/StringExtension.h"
#include <SDL_image.h>
#include <filesystem>

using namespace std;
namespace Toolset {
	void TextureHandler::load(SDL_Renderer* renderer)
	{
		for (const auto& file : std::filesystem::directory_iterator(PATH)) {
			std::filesystem::path path = file.path();
			string s_path = path.generic_u8string();
			SDL_Texture* temp = loadtexture(renderer, s_path.c_str());
			vector<string> tokens;
			tokens = StringExtension::Split(s_path, '/');
			if (temp != nullptr) add(tokens.at(tokens.size() - 1).c_str(), temp);
		}
	}

	SDL_Texture* TextureHandler::loadtexture(SDL_Renderer* renderer, const char* path)
	{
		SDL_Texture* texture = IMG_LoadTexture(renderer, path);
		if (texture == nullptr) {
			SDL_Log("ERROR::IMG_LOADTEXTURE FAILED : %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		return texture;
	}

	void TextureHandler::init()
	{
		if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
			SDL_Log("ERROR::IMG_INIT::FAILED : %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	void TextureHandler::destroy()
	{
	}

	void TextureHandler::add(const char* key, SDL_Texture* texture)
	{
	}

	void TextureHandler::remove(const char* key)
	{
	}

	SDL_Texture* TextureHandler::get(const char* key)
	{
		return nullptr;
	}
}