#pragma once
#include "SceneObject.h"
#include "CtrlComponent.h"
#include "ModelComponent.h"
#include "ViewComponent.h"
#include "State.h"

namespace ieg
{
	class Minigin;

	class GameObject final
		: public SceneObject
	{
	public:
		explicit GameObject(Scene* pScene);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<class T>
		T* CreateCtrlComponent(Minigin* pEngine, ...)
		{
			std::va_list args{};
			va_start(args, pEngine);
			T* pCtrlComponent{ new T{ this, pEngine, args } };
			va_end(args);
			if (pCtrlComponent != nullptr)
				mpCtrlComponents.push_back(pCtrlComponent);
			return pCtrlComponent;
		}

		template<class T>
		T* CreateModelComponent(Minigin* pEngine,...)
		{
			std::va_list args{};
			va_start(args, pEngine);
			T* pModelComponent{ new T{ this, pEngine, args } };
			va_end(args);
			if (pModelComponent != nullptr)
				mpModelComponents.push_back(pModelComponent);
			return pModelComponent;
		}

		template<class T>
		T* CreateViewComponent(Minigin* pEngine,...)
		{
			T* pViewComponent{ new T{ pEngine } };
			if (pViewComponent != nullptr)
				mpViewComponents.push_back(pViewComponent);
			return pViewComponent;
		}

		template<class T>
		const T* GetCtrlComponent() const
		{
			for (const auto pCtrlComponent : mpCtrlComponents)
				if (typeid(*pCtrlComponent).hash_code() == typeid(T).hash_code())
					return (T*)pCtrlComponent;
			return nullptr;
		};
		template<class T>
		T* GetCtrlComponent()
		{
			for (auto pCtrlComponent : mpCtrlComponents)
				if (typeid(*pCtrlComponent).hash_code() == typeid(T).hash_code())
					return (T*)pCtrlComponent;
			return nullptr;
		};

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
					return (T*)pModelComponent;
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
					return (T*)pViewComponent;
			return nullptr;
		};

		void CtrlUpdate(const float deltaTime) override;
		void ModelUpdate(const float deltaTime) override;
		void ModelCollision() override;
		void ModelSwitch() override;
		void ViewUpdate(const float deltaTime) override;
		void ViewRender() const override;

		const bool& IsActive() const { return mIsActive; };
		void SetIsActive(bool isActive) { mIsActive = isActive; };
	private:
		bool mIsActive;
		std::vector<CtrlComponent*> mpCtrlComponents;
		std::vector<ModelComponent*> mpModelComponents;
		std::vector<ViewComponent*> mpViewComponents;
	};
}
