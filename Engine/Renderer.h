#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace ieg
{
	class Texture2D;
	class SceneManager;

	class Renderer final
		: public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render(SceneManager* pSceneManager) const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;
	private:
		SDL_Renderer* mpRenderer{};
	};
}
