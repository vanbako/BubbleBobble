#pragma once
#include "../Engine/ModelComponent.h"

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

		virtual void Update(const float deltaTime) override;

		void SetStartScene(Scene* pScene);
		void SetRenderComponent(RenderViewComponent* pRenderComponent);
		void SetTexture(Texture2D* pTexture, size_t num);
	private:
		Scene* mpStartScene;
		Audio* mpAudio;
		size_t mStartSoundId;
		float mStartWait;
		bool mPlaySound;
		size_t mScreen;
		float mSwapWait;
		Texture2D* mpTexture2D[2];
		RenderViewComponent* mpRenderComponent;

		static const float mStartWaitVal;
		static const float mSwapWaitVal;
	};
}
