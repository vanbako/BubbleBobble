#pragma once
#include "SceneObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include <cstdarg>

namespace ieg
{
	class Minigin;
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

		template<class T>
		T* CreateComponent(Minigin* pEngine...)
		{
			T* pComponent{ new T{ pEngine } };
			if (pComponent != nullptr)
				mpComponents.push_back(pComponent);
			return pComponent;
		}
		template<>
		TextComponent* CreateComponent(Minigin* pEngine...)
		{
			std::va_list args;
			va_start(args, pEngine);
			Font* pFont{ va_arg(args, Font*) };
			va_end(args);
			TextComponent* pComponent{ new TextComponent{ pEngine, pFont } };
			if (pComponent != nullptr)
				mpComponents.push_back(pComponent);
			return pComponent;
		}
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
