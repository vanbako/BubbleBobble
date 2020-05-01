#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class Audio;
	class SceneManager;
	class Scene;

	class IntroComponent final
		: public ModelComponent
	{
	public:
		explicit IntroComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~IntroComponent() = default;
		IntroComponent(const IntroComponent&) = delete;
		IntroComponent(IntroComponent&&) = delete;
		IntroComponent& operator=(const IntroComponent&) = delete;
		IntroComponent& operator=(IntroComponent&&) = delete;

		virtual void Update(const float deltaTime) override;

		void SetStartScene(Scene* pScene);

		void Start() const;
	private:
		Scene* mpStartScene;
		Audio* mpAudio;
		int mStartSoundId;
		int mIntroSoundId;
		float mStartWait;
		bool mStartAudio;
	};
}
