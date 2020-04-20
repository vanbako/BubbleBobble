#pragma once
#include "../Engine/Component.h"

namespace ieg
{
	class Minigin;
	class Audio;
	class SceneManager;
	class Scene;

	class IntroComponent final
		: public Component
	{
	public:
		explicit IntroComponent(Minigin* pEngine);
		~IntroComponent() = default;

		virtual void Update(const float deltaTime) override;
		virtual void Render() const override {};

		void SetStartScene(Scene* pScene);

		void Start() const;
	private:
		Minigin* mpEngine;
		Scene* mpStartScene;
		Audio* mpAudio;
		size_t mStartSoundId;
		size_t mIntroSoundId;
		float mStartWait;
		bool mStartAudio;
	};
}
