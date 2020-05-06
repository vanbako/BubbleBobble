#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class GameObject;
	class Audio;
	class BufferManager;
	class Scene;
	class ColorRGBA8;

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

		void InitGameObjects(GameObject* pGOLevel);
		GameObject* GetAvatar(int avatar);
		GameObject** GetBubbles(int avatar);
		GameObject* GetLevel();
		void NextLevel();

		static const int GetAvatarMax() { return mpAvatarMax; };
		static const int GetBubblesPerAvatarMax() { return mpBubblesPerAvatarMax; };
	private:
		BufferManager* mpBufferManager;
		int mLevel;
		GameObject** mppGOAvatars;
		GameObject** mppGOBubbles;
		GameObject* mpGOLevel;
		Audio* mpAudio;
		int mSoundId;
		bool mIsSoundPlaying;
		bool mEndLevel;

		void CreateAvatars(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette);
		void CreateBubbles(Minigin* pEngine, Scene* pScene, ColorRGBA8* pPalette);

		static const int mpAvatarMax{ 2 };
		static const int mpBubblesPerAvatarMax;
		static const Vec2<int> mpAvatarInitialPos[mpAvatarMax];
	};
}
