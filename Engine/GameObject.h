#pragma once
#include "SceneObject.h"
#include "ModelComponent.h"
#include "ViewComponent.h"
#include "TextViewComponent.h"
#include "State.h"
#include <cstdarg>

namespace ieg
{
	class Minigin;

	class GameObject final
		: public SceneObject
	{
	public:
		explicit GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<class T>
		T* CreateModelComponent(Minigin* pEngine...)
		{
			T* pModelComponent{ new T{ pEngine } };
			if (pModelComponent != nullptr)
			{
				pModelComponent->SetGameObject(this);
				mpModelComponents.push_back(pModelComponent);
			}
			return pModelComponent;
		}

		template<class T>
		T* CreateViewComponent(Minigin* pEngine...)
		{
			T* pViewComponent{ new T{ pEngine } };
			if (pViewComponent != nullptr)
				mpViewComponents.push_back(pViewComponent);
			return pViewComponent;
		}
		template<>
		TextViewComponent* CreateViewComponent(Minigin* pEngine...)
		{
			std::va_list args;
			va_start(args, pEngine);
			Font* pFont{ va_arg(args, Font*) };
			va_end(args);
			TextViewComponent* pViewComponent{ new TextViewComponent{ pEngine, pFont } };
			if (pViewComponent != nullptr)
				mpViewComponents.push_back(pViewComponent);
			return pViewComponent;
		}

		template<class T>
		T* CreateOrReplaceState()
		{
			if (mpState != nullptr)
				delete mpState;
			T* mpState{ new T{} };
			if (mpState != nullptr)
				mpState->SetGameObject(this);
			return mpState;
		}

		void ReplaceState(State* pState)
		{
			if (pState == nullptr)
				return;
			if (mpState != nullptr)
				delete mpState;
			mpState = pState;
			mpState->SetGameObject(this);
		}

		template<class T>
		const T* GetModelComponent() const
		{
			for (const auto pModelComponent : mpModelComponents)
				if (typeid(*pModelComponent).hash_code() == typeid(T).hash_code())
					return (T*)pModelComponent;
			return nullptr;
		};
		template<class T>
		T* GetModelComponent()
		{
			for (auto pModelComponent : mpModelComponents)
				if (typeid(*pModelComponent).hash_code() == typeid(T).hash_code())
					return pModelComponent;
			return nullptr;
		};

		template<class T>
		const T* GetViewComponent() const
		{
			for (const auto pViewComponent : mpViewComponents)
				if (typeid(*pViewComponent).hash_code() == typeid(T).hash_code())
					return (T*)pViewComponent;
			return nullptr;
		};
		template<class T>
		T* GetViewComponent()
		{
			for (auto pViewComponent : mpViewComponents)
				if (typeid(*pViewComponent).hash_code() == typeid(T).hash_code())
					return pViewComponent;
			return nullptr;
		};

		State* GetState();

		void Update(const float deltaTime) override;
		void Render() const override;
	private:
		std::vector<ModelComponent*> mpModelComponents;
		std::vector<ViewComponent*> mpViewComponents;
		State* mpState;
	};
}
