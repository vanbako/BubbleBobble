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

		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		HudObserver* GetObserver();
		GameObject* GetLevel();
		void NextLevel();
	private:
		BufferManager* mpBufferManager;
		int mLevel;
		GameObject** mppGOAvatars;
		ObjectsManager* mpObjectsManager;
		GameObject* mpGOLevel;
		Audio* mpAudio;
		HudObserver* mpHudObserver;
		int mSoundId;
		bool mIsSoundPlaying;
		bool mEndLevel;
	};
}
