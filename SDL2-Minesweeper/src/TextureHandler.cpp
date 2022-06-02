#pragma once
#include "../headers/TextureHandler.h"
#include "../headers/StringExtension.h"

#include <SDL_image.h>
#include <filesystem>

#ifndef MY_RESOURCES_PATH
#define MY_RESOURCES_PATH "/res/sprites"
#endif

namespace Toolset {
	unordered_map<string, SDL_Texture*> TextureHandler::textures;

	void TextureHandler::load(SDL_Renderer* renderer)
	{
		std::filesystem::path build_path = std::filesystem::current_path().parent_path();
		string res_path = build_path.generic_u8string() + MY_RESOURCES_PATH;
		for (const auto& file : std::filesystem::directory_iterator(res_path)) {
			std::filesystem::path path = file.path();
			string s_path = path.generic_u8string();
			SDL_Texture* temp = loadtexture(renderer, s_path.c_str());
			vector<string> tokens;
			tokens = StringExtension::Split(s_path, '/');
			if (temp != nullptr) add(tokens.at(tokens.size() - 1).c_str(), temp);
		}
	}

	SDL_Texture* TextureHandler::loadtexture(SDL_Renderer* renderer, string path)
	{
		SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
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
		for (auto& it : textures) SDL_DestroyTexture(it.second);
		textures.clear();
		IMG_Quit();
	}

	void TextureHandler::add(string key, SDL_Texture* texture)
	{
		textures.insert(make_pair(key, texture));
	}

	void TextureHandler::remove(string key)
	{
		if (textures.find(key) != textures.end()) {
			SDL_DestroyTexture(textures.at(key));
			textures.erase(key);
		}
	}

	SDL_Texture* TextureHandler::get(string key)
	{
		if (textures.find(key) != textures.end()) return textures[key];
		else return nullptr;
	}
}