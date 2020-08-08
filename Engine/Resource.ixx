export module Engine:Resource;

import std.core;

struct _TTF_Font;
struct SDL_Texture;

namespace ieg
{
	class Renderer;

	class Texture2D final
	{
	public:
		explicit Texture2D(SDL_Texture* pTexture);
		~Texture2D();
		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&&) = delete;

		SDL_Texture* GetSDLTexture() const;
	private:
		SDL_Texture* mpTexture;
	};

	export class Font final
	{
	public:
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();
		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator=(const Font&) = delete;
		Font& operator=(Font&&) = delete;

		_TTF_Font* GetFont() const;
	private:
		_TTF_Font* mFont;
		unsigned int mSize;
	};

	export class ResourceManager final
	{
	public:
		explicit ResourceManager(const std::string& dataPath);
		~ResourceManager();
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		Texture2D* LoadTexture(const std::string& file, Renderer* pRenderer);
		void RemoveTexture(Texture2D* pTexture);
		Texture2D* CreateTexture(SDL_Texture* pSDLTexture);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		std::string mDataPath;
		std::set<Texture2D*> mpTextures;
		std::vector<Font*> mpFonts;
	};
}
