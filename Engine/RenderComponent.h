#pragma once
#include "Component.h"

namespace ieg
{
	class ResourceManager;
	class Texture2D;
	class TransformComponent;
	class ResourceManager;

	class RenderComponent
		: public Component
	{
	public:
		explicit RenderComponent(ResourceManager* pResourceManager);
		~RenderComponent() = default;

		void Update(const float deltaTime) { (deltaTime); };
		void Render() const;

		void SetTransformComponent(TransformComponent* pTransformComponent);
		void SetTexture(const std::string& file);
		void SetTexture(Texture2D* pTexture);
	private:
		ResourceManager* mpResourceManager;
		TransformComponent* mpTransformComponent;
		Texture2D* mpTexture;
	};
}
