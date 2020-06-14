#pragma once
#include "NpcComponent.h"

namespace ieg
{
	class Minigin;
	class GameObject;
	class Audio;
	class BufferManager;
	class Scene;
	class ColorRGBA8;
	class HudObserver;
	class ObjectsManager;

	class HudComponent final
		: public ModelComponent
	{
	public:
		explicit HudComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~HudComponent();
		HudComponent(const HudComponent&) = delete;
		HudComponent(HudComponent&&) = delete;
		HudComponent& operator=(const HudComponent&) = delete;
		HudComponent& operator=(HudComponent&&) = delete;

		void OnSceneActivation(int value) override;
		void OnSceneDeactivation(int value) override;
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		HudObserver* GetObserver();
		GameObject* GetLevel();
		void NextLevel();

		void DeltaScore(int value);
		void AvatarDie(int value);
		void GameOver();
	private:
		int mPlayers;
		Audio* mpAudio;
		BufferManager* mpBufferManager;
		ColorRGBA8* mpPalette;
		Scene* mpIntroScene;
		int mLevel;
		int mGameSoundId;
		ObjectsManager* mpObjectsManager;
		GameObject* mpGOLevel;
		HudObserver* mpHudObserver;
		bool mIsSoundPlaying;
		bool mEndLevel;
		std::vector<int> mScores;
		std::vector<int> mLives;
		std::vector<GameObject*> mpGOScores;
		std::vector<GameObject*> mpGOLives;

		static const int mColorIndex[];
		static const int mStartLives;
		static const int mMaxLives;

		void CreateScores();
		void CreateLives();
		void DrawLives();
		void DrawScores();
		void LivesInit();
		void ScoresInit();
	};
}
