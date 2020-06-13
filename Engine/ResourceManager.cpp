#include "pch.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

using namespace ieg;

ResourceManager::ResourceManager(const std::string& dataPath)
	: mDataPath{ dataPath }
	, mpTextures{}
	, mpFonts{}
{
	// load support for png and jpg, this takes a while!
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());

	if (TTF_Init() != 0)
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
}

ResourceManager::~ResourceManager()
{
	for (auto& pTexture : mpTextures)
		delete pTexture;
	for (auto& pFont : mpFonts)
		delete pFont;
}

Texture2D* ResourceManager::LoadTexture(const std::string& file, Renderer* pRenderer)
{
	const std::string fullPath{ mDataPath + file };
	SDL_Texture* pTexture{ IMG_LoadTexture(pRenderer->GetSDLRenderer(), fullPath.c_str()) };
	if (pTexture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	Texture2D* pTexture2D{ new Texture2D{ pTexture } };
	mpTextures.insert(pTexture2D);
	return pTexture2D;
}

void ResourceManager::RemoveTexture(Texture2D* pTexture)
{
	delete pTexture;
	mpTextures.erase(pTexture);
}

Texture2D* ResourceManager::CreateTexture(SDL_Texture* pSDLTexture)
{
	Texture2D* texture2D{ new Texture2D{ pSDLTexture } };
	mpTextures.insert(texture2D);
	return texture2D;
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	Font* pFont{ new Font{mDataPath + file, size} };
	mpFonts.push_back(pFont);
	return pFont;
}
