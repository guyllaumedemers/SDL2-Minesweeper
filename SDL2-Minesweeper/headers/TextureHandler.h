#pragma once
#include "StringExtension.h"
#include <filesystem>
#include <unordered_map>
#include <string>
#include <vector>

#ifndef MY_RESOURCES_PATH
#define MY_RESOURCES_PATH "/res/sprites"
#endif
//#ifdef SDL
#include <SDL.h>
#include <SDL_image.h>
//#endif

using namespace std;
namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	class TextureHandler {
	private:
		typedef GraphicAPIsTexture* (*FuncPtr)(GraphicAPIsRendering*, string);
		static unordered_map<string, GraphicAPIsTexture*> textures;
		TextureHandler(const TextureHandler&) = delete;
		TextureHandler(TextureHandler&&) = delete;
		TextureHandler() = delete;
		static GraphicAPIsTexture* loadtexture(GraphicAPIsRendering*, string);
		static void add(string key, GraphicAPIsTexture*);
		static void remove(string key);
	public:
		static void init();
		static void load(GraphicAPIsRendering*, FuncPtr);
		static void destroy();
		static GraphicAPIsTexture* get(string);
	};

	/// <summary>
	/// static fields
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	unordered_map<string, GraphicAPIsTexture*> TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::textures;

	/// <summary>
	/// loading all textures at path
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::load(GraphicAPIsRendering* renderer, FuncPtr funcptr)
	{
		std::filesystem::path build_path = std::filesystem::current_path().parent_path();
		string res_path = build_path.generic_u8string() + MY_RESOURCES_PATH;
		for (const auto& file : std::filesystem::directory_iterator(res_path)) {
			std::filesystem::path path = file.path();
			string s_path = path.generic_u8string();
			GraphicAPIsTexture* temp = funcptr(renderer, s_path.c_str());
			vector<string> tokens;
			tokens = StringExtension::Split(s_path, '/');
			if (temp != nullptr) add(tokens.at(tokens.size() - 1).c_str(), temp);
		}
	}

	/// <summary>
	/// loading of single texture
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	GraphicAPIsTexture* TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::loadtexture(GraphicAPIsRendering* renderer, string path)
	{
		/// <summary>
		/// Shouldnt be specific but at this point this is becoming stupid
		/// </summary>
		SDL_Texture* texture = IMG_LoadTexture((SDL_Renderer*)renderer, path.c_str());
		if (texture == nullptr) {
			SDL_Log("ERROR::IMG_LOADTEXTURE FAILED : %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		return texture;
	}

	/// <summary>
	/// initialization of the lib for texture loading, should be more modular for different GraphicAPIs lib
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::init()
	{
		/// <summary>
		/// same here
		/// </summary>
		if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
			SDL_Log("ERROR::IMG_INIT::FAILED : %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	/// <summary>
	/// clear all textures ressources
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::destroy()
	{
		for (auto& it : textures) SDL_DestroyTexture((SDL_Texture*)it.second);
		textures.clear();
		IMG_Quit();
	}

	/// <summary>
	/// adding entry
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::add(string key, GraphicAPIsTexture* texture)
	{
		textures.insert({ key, texture });
	}

	/// <summary>
	/// removing entry
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::remove(string key)
	{
		if (textures.find(key) != textures.end()) {
			SDL_DestroyTexture((SDL_Texture*)textures.at(key));
			textures.erase(key);
		}
	}

	/// <summary>
	/// accessing entry
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	GraphicAPIsTexture* TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::get(string key)
	{
		if (textures.find(key) != textures.end()) return textures[key];
		else return nullptr;
	}
}