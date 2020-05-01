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
		explicit Renderer();
		~Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;

		void Init(SDL_Window* window);
		void Render(SceneManager* pSceneManager) const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, Vec2<size_t> pos) const;
		void RenderTexture(const Texture2D& texture, Vec2<size_t> srcPos, Vec2<size_t> srcSize, Vec2<size_t> dstPos) const;

		SDL_Renderer* GetSDLRenderer() const;
	private:
		SDL_Renderer* mpSDLRenderer{};

		static const size_t mGlobalScale;
	};
}
