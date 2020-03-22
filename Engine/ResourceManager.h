#pragma once
#include <set>

namespace ieg
{
	class Texture2D;
	class Font;
	class Renderer;

	class ResourceManager final
	{
	public:
		explicit ResourceManager(const std::string& dataPath);
		~ResourceManager();
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator= (const ResourceManager&) = delete;
		ResourceManager& operator= (const ResourceManager&&) = delete;

		Texture2D* LoadTexture(const std::string& file, Renderer* pRenderer);
		void RemoveTexture(Texture2D* pTexture);
		void AddTexture(Texture2D* pTexture);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		std::string mDataPath;
		std::set<Texture2D*> mpTextures;
		std::vector<Font*> mpFonts;
	};
}
