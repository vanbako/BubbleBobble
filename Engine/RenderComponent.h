#pragma once
#include "Component.h"

struct SDL_Texture;

namespace ieg
{
	class ResourceManager;
	class Texture2D;
	class TransformComponent;
	class ResourceManager;
	class Renderer;

	class RenderComponent final
		: public Component
	{
	public:
		explicit RenderComponent(ResourceManager* pResourceManager, Renderer* pRenderer);
		~RenderComponent() = default;

		void Update(const float deltaTime) { (deltaTime); };
		void Render() const;

		void SetTransformComponent(TransformComponent* pTransformComponent);
		void SetTexture(const std::string& file);
		void SetTexture(Texture2D* pTexture);
		Texture2D* SetTexture(SDL_Texture* pSDLTexture);
	private:
		ResourceManager* mpResourceManager;
		Renderer* mpRenderer;
		TransformComponent* mpTransformComponent;
		Texture2D* mpTexture;
	};
}
