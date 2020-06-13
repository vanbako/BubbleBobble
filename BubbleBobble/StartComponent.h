#pragma once

namespace ieg
{
	class Minigin;
	class Audio;
	class SceneManager;
	class Scene;
	class Texture2D;
	class RenderViewComponent;

	class StartComponent final
		: public ModelComponent
	{
	public:
		explicit StartComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~StartComponent() = default;
		StartComponent(const StartComponent&) = delete;
		StartComponent(StartComponent&&) = delete;
		StartComponent& operator=(const StartComponent&) = delete;
		StartComponent& operator=(StartComponent&&) = delete;

		void OnSceneActivation(int value) override;
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		void SetStartScene(Scene* pScene);
	private:
		int mPlayers;
		Scene* mpStartScene;
		Audio* mpAudio;
		int mStartSoundId;
		float mStartWait;
		bool mPlaySound;
		float mSwapWait;

		static const float mStartWaitVal;
	};
}
