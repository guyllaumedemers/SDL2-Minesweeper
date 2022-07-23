
#ifndef INCLUDED_TEXTUREHANDLER
#define INCLUDED_TEXTUREHANDLER

#ifndef MY_RESOURCES_PATH
#define MY_RESOURCES_PATH "/res/sprites"
#endif

#include "StringExtension.h"
#include <SDL.h>
#include <SDL_image.h>	// should be reference here -> bad idea
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	class TextureHandler {
		typedef GraphicAPIsTexture* (*FuncPtr)(GraphicAPIsRendering*, std::string);
		inline static std::unordered_map<std::string, GraphicAPIsTexture*> textures;
		static void add(std::string key, GraphicAPIsTexture*);
		static void remove(std::string key);
	public:
		TextureHandler(const TextureHandler&) = delete;
		TextureHandler(TextureHandler&&) = delete;
		TextureHandler() = delete;
		~TextureHandler();
		TextureHandler& operator=(const TextureHandler&) = delete;
		TextureHandler& operator=(TextureHandler&&) = delete;
		static GraphicAPIsTexture* get(std::string);
		static void init();
		static void load(GraphicAPIsRendering*, FuncPtr);
		static void destroy();
	};
	
	template <class GraphicAPIsRendering, class GraphicAPIsTexture>
	TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::~TextureHandler()
	{}

	/// <summary>
	/// SDL Specific -> bad idea
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::init()
	{
		if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
			SDL_Log("ERROR::IMG_INIT::FAILED : %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	/// <summary>
	/// SDL Specific -> bad idea
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::destroy()
	{
		for (auto& it : textures) SDL_DestroyTexture((SDL_Texture*)it.second);
		textures.clear();
		IMG_Quit();
	}

	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::add(std::string key, GraphicAPIsTexture* texture)
	{
		textures.insert({ key, texture });
	}

	/// <summary>
	/// SDL Specific -> bad idea
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::remove(std::string key)
	{
		if (textures.find(key) != textures.end()) {
			SDL_DestroyTexture((SDL_Texture*)textures.at(key));
			textures.erase(key);
		}
	}
	
	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	void TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::load(GraphicAPIsRendering* renderer, FuncPtr funcptr)
	{
		std::filesystem::path build_path = std::filesystem::current_path().parent_path();
		std::string res_path = build_path.generic_u8string() + MY_RESOURCES_PATH;
		for (const auto& file : std::filesystem::directory_iterator(res_path)) {
			std::filesystem::path path = file.path();
			std::string s_path = path.generic_u8string();
			GraphicAPIsTexture* temp = funcptr(renderer, s_path.c_str());
			std::vector<std::string> tokens;
			tokens = StringExtension::Split(s_path, '/');
			if (temp != nullptr) add(tokens.at(tokens.size() - 1).c_str(), temp);
		}
	}

	template<class GraphicAPIsRendering, class GraphicAPIsTexture>
	GraphicAPIsTexture* TextureHandler<GraphicAPIsRendering, GraphicAPIsTexture>::get(std::string key)
	{
		if (textures.find(key) != textures.end()) return textures[key];
		return nullptr;
	}
}
#endif