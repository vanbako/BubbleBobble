#pragma once
#include <set>

namespace ieg
{
	class Texture2D;
	class Font;

	class ResourceManager final
	{
	public:
		ResourceManager(const std::string& dataPath);
		~ResourceManager();
		Texture2D* LoadTexture(const std::string& file);
		void RemoveTexture(Texture2D* pTexture);
		void AddTexture(Texture2D* pTexture);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		std::string mDataPath;
		std::set<Texture2D*> mpTextures;
		std::vector<Font*> mpFonts;
	};
}
