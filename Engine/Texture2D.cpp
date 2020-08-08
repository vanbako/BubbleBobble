module Engine:Resource;

using namespace ieg;

Texture2D::Texture2D(SDL_Texture* pTexture)
	: mpTexture{ pTexture }
{
}

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mpTexture);
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return mpTexture;
}
