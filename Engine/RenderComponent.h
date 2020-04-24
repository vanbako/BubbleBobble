#pragma once
#include "Component.h"

struct SDL_Texture;

namespace ieg
{
	class Minigin;
	class Texture2D;
	class TransformComponent;

	class RenderComponent final
		: public Component
	{
	public:
		explicit RenderComponent(Minigin* pEngine);
		~RenderComponent() = default;
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&) = delete;

		void Update(const float deltaTime) { (deltaTime); };
		void Render() const;

		void SetTransformComponent(TransformComponent* pTransformComponent);
		void SetTexture(const std::string& file);
		void SetTexture(Texture2D* pTexture);
		void SetSize(float width, float height);
		void SetIndex(size_t index);
		Texture2D* SetTexture(SDL_Texture* pSDLTexture);
		Texture2D* ReplaceTexture(SDL_Texture* pSDLTexture);
	private:
		TransformComponent* mpTransformComponent;
		Texture2D* mpTexture;
		float mWidth;
		float mHeight;
		size_t mIndex;
	};
}
