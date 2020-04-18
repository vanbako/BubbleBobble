#pragma once
#include "../Engine/Component.h"

namespace ieg
{
	class Audio;
	class SceneManager;
	class Scene;

	class IntroComponent final
		: public Component
	{
	public:
		explicit IntroComponent() = default;
		~IntroComponent() = default;

		virtual void Update(const float deltaTime) override { (deltaTime); };
		virtual void Render() const override {};

		void SetSceneManager(SceneManager* pSceneManager);
		void SetStartScene(Scene* pScene);

		void Start() const;
	private:
		SceneManager* mpSceneManager;
		Scene* mpStartScene;
	};
}
