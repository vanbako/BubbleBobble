#pragma once
#include "SceneObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include <cstdarg>

namespace ieg
{
	//class ResourceManager;

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
		T* CreateComponent(int count...)
		{
			(count);
			T* pComponent{ new T{} };
			if (pComponent != nullptr)
				mpComponents.push_back(pComponent);
			return pComponent;
		}
		template<>
		RenderComponent* CreateComponent(int count...)
		{
			std::va_list args;
			va_start(args, count);
			Renderer* pRenderer{ va_arg(args, Renderer*) };
			va_end(args);
			RenderComponent* pComponent{ new RenderComponent{ mpRes, pRenderer } };
			if (pComponent != nullptr)
				mpComponents.push_back(pComponent);
			return pComponent;
		}
		template<>
		TextComponent* CreateComponent(int count...)
		{
			std::va_list args;
			va_start(args, count);
			Font* pFont{ va_arg(args, Font*) };
			Renderer* pRenderer{ va_arg(args, Renderer*) };
			va_end(args);
			TextComponent* pComponent{ new TextComponent{ pFont, pRenderer } };
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
