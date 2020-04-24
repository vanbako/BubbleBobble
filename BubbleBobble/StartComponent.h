#pragma once
#include "../Engine/Component.h"

namespace ieg
{
	class Minigin;
	class Audio;
	class SceneManager;
	class Scene;
	class Texture2D;
	class RenderComponent;

	class StartComponent final
		: public Component
	{
	public:
		explicit StartComponent(Minigin* pEngine);
		~StartComponent() = default;
		StartComponent(const StartComponent&) = delete;
		StartComponent(StartComponent&&) = delete;
		StartComponent& operator= (const StartComponent&) = delete;
		StartComponent& operator= (const StartComponent&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Render() const override {};

		void SetStartScene(Scene* pScene);
		void SetRenderComponent(RenderComponent* pRenderComponent);
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
		RenderComponent* mpRenderComponent;

		static const float mStartWaitVal;
		static const float mSwapWaitVal;
	};
}
