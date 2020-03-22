#pragma once
#include "SceneObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"

namespace ieg
{
	class ResourceManager;

	class GameObject final
		: public SceneObject
	{
	public:
		explicit GameObject(ResourceManager* pRes);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Add(Component* pComponent);
		template<class T>
		const T* GetComponent() const
		{
			for (const auto pComponent : mpComponents)
				if (typeid(*pComponent).hash_code() == typeid(T).hash_code())
					return (T*)pComponent;
			return nullptr;
		};
		template<class T>
		T* GetComponent()
		{
			for (auto pComponent : mpComponents)
				if (typeid(*pComponent).hash_code() == typeid(T).hash_code())
					return pComponent;
			return nullptr;
		};

		void Update(const float deltaTime) override;
		void Render() const override;
	private:
		ResourceManager* mpRes;
		std::vector<Component*> mpComponents;
	};
}
