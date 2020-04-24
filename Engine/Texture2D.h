#pragma once

struct SDL_Texture;

namespace ieg
{
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
}
