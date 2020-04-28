#pragma once
#include "ViewComponent.h"

struct SDL_Texture;

namespace ieg
{
	class Minigin;
	class Texture2D;
	class TransformModelComponent;

	class RenderViewComponent final
		: public ViewComponent
	{
	public:
		explicit RenderViewComponent(Minigin* pEngine);
		~RenderViewComponent() = default;
		RenderViewComponent(const RenderViewComponent&) = delete;
		RenderViewComponent(RenderViewComponent&&) = delete;
		RenderViewComponent& operator=(const RenderViewComponent&) = delete;
		RenderViewComponent& operator=(RenderViewComponent&&) = delete;

		void Update(const float deltaTime) { (deltaTime); };
		void Render() const;

		void SetTransformComponent(TransformModelComponent* pTransformComponent);
		void SetTexture(const std::string& file);
		void SetTexture(Texture2D* pTexture);
		void SetSize(float width, float height);
		void SetIndex(size_t index);
		Texture2D* SetTexture(SDL_Texture* pSDLTexture);
		Texture2D* ReplaceTexture(SDL_Texture* pSDLTexture);
	private:
		TransformModelComponent* mpTransformComponent;
		Texture2D* mpTexture;
		float mWidth;
		float mHeight;
		size_t mIndex;
	};
}
