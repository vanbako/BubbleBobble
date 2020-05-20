#pragma once
#include "ViewComponent.h"

struct SDL_Texture;

namespace ieg
{
	class Minigin;
	class Texture2D;
	class TransformModelComponent;

	class RenderViewComponent final
		: public ViewComponent
	{
	public:
		explicit RenderViewComponent(Minigin* pEngine);
		~RenderViewComponent() = default;
		RenderViewComponent(const RenderViewComponent&) = delete;
		RenderViewComponent(RenderViewComponent&&) = delete;
		RenderViewComponent& operator=(const RenderViewComponent&) = delete;
		RenderViewComponent& operator=(RenderViewComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Render() const override;

		void SetTransformComponent(TransformModelComponent* pTransformComponent);
		void SetTexture(const std::string& file);
		void SetTexture(Texture2D* pTexture);
		Texture2D* GetTexture();
		void SetSize(int width, int height);
		void SetIndex(int index);
		void SetType(int type);
		void SetAnimation(float delay, int startIndex, int stopIndex);
		Texture2D* SetTexture(SDL_Texture* pSDLTexture);
		Texture2D* ReplaceTexture(SDL_Texture* pSDLTexture);
		void SetIsSprite(bool isSprite);
	private:
		TransformModelComponent* mpTransformComponent;
		Texture2D* mpTexture;
		Vec2<int> mSize;
		int mIndex;
		int mType;
		float
			mDelay,
			mCurrDelay;
		int
			mStartIndex,
			mStopIndex;
		bool mIsAnimating;
		bool mIsSprite;
	};
}
