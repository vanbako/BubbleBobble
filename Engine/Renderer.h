#pragma once

struct SDL_Window;
struct SDL_Renderer;

namespace ieg
{
	class Texture2D;
	class SceneManager;

	class Renderer final
	{
	public:
		explicit Renderer() = default;
		~Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator= (const Renderer&) = delete;
		Renderer& operator= (const Renderer&&) = delete;

		void Init(SDL_Window* window);
		void Render(SceneManager* pSceneManager) const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;
	private:
		SDL_Renderer* mpSDLRenderer{};
	};
}
