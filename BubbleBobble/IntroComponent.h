#pragma once

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
		~IntroComponent();
		IntroComponent(const IntroComponent&) = delete;
		IntroComponent(IntroComponent&&) = delete;
		IntroComponent& operator=(const IntroComponent&) = delete;
		IntroComponent& operator=(IntroComponent&&) = delete;

		void OnSceneActivation(int value) override;
		void OnSceneDeactivation(int value) override;
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		void SetStartScene(Scene* pScene);

		void Start(int players) const;
	private:
		Scene* mpStartScene;
		Audio* mpAudio;
		int mStartSoundId;
		int mIntroSoundId;
		float mStartWait;
		bool mStartAudio;
	};
}
