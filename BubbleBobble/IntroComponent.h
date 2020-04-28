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
		explicit IntroComponent(Minigin* pEngine);
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
		size_t mStartSoundId;
		size_t mIntroSoundId;
		float mStartWait;
		bool mStartAudio;
	};
}
