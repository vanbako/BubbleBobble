#pragma once
#include "NpcComponent.h"
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class GameObject;
	class Audio;
	class BufferManager;
	class Scene;
	class ColorRGBA8;
	class HudObserver;

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

		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		HudObserver* GetObserver();
		void InitGameObjects(GameObject* pGOLevel);
		void SpawnNpc(NpcType npcType, Vec2<int>& pos, int wait);
		GameObject* GetAvatar(int avatar);
		GameObject** GetBubbles(int avatar);
		GameObject* GetLevel();
		void NextLevel();
		void FireBubble(const Vec2<int>& pos);

		static const int GetAvatarMax() { return mpAvatarMax; };
		static const int GetBubblesPerAvatarMax() { return mpBubblesPerAvatarMax; };
	private:
		static const int mNpcMax{ 6 };
		BufferManager* mpBufferManager;
		int mLevel;
		GameObject** mppGOAvatars;
		GameObject** mppGOBubbles;
		GameObject** mppGONpcs;
		float mSpawnWait[mNpcMax];
		GameObject* mpGOLevel;
		Audio* mpAudio;
		HudObserver* mpHudObserver;
		int mSoundId;
		bool mIsSoundPlaying;
		bool mEndLevel;

		void CreateAvatars(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette);
		void CreateBubbles(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette);
		void CreateNpcs(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette);
		int GetIdleNpc();

		static const int mpAvatarMax{ 2 };
		static const int mpBubblesPerAvatarMax;
		static const Vec2<int> mpAvatarInitialPos[mpAvatarMax];
	};
}
