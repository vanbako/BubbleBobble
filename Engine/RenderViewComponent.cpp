#include "pch.h"
#include "RenderViewComponent.h"
#include "TransformModelComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Minigin.h"

using namespace ieg;

RenderViewComponent::RenderViewComponent(Minigin* pEngine)
	: ViewComponent(pEngine)
	, mpTransformComponent{ nullptr }
	, mpTexture{ nullptr }
	, mSize{}
	, mIndex{ 0 }
	, mType{ 0 }
	, mDelay{ 0.f }
	, mCurrDelay{ 0.f }
	, mIsOnOff{ false }
	, mIsOn{ true }
	, mOnOffDelay{ 0.15f }
	, mCurrOnOffDelay{ 0.f }
	, mStartIndex{ 0 }
	, mStopIndex{ 0 }
	, mIsAnimating{ false }
	, mIsSprite{ false }
{
}

void RenderViewComponent::Update(const float deltaTime)
{
	if (mIsAnimating)
	{
		mCurrDelay -= deltaTime;
		if (mCurrDelay <= 0.f)
		{
			mCurrDelay += mDelay;
			mIndex += 1;
			if (mIndex > mStopIndex)
				mIndex = mStartIndex;
		}
	}
	if (mIsSprite)
	{
		mIndex = mType;
		if (mpTransformComponent->GetIsLookingLeft())
			mIndex += 8;
		mIndex += (mpTransformComponent->GetPos().GetX() % 16) / 2;
	}
	if (mIsOnOff)
	{
		mCurrOnOffDelay -= deltaTime;
		if (mCurrOnOffDelay <= 0.f)
		{
			mCurrOnOffDelay += mOnOffDelay;
			mIsOn = !mIsOn;
		}
	}
}

void RenderViewComponent::Render() const
{
	if (mIsOnOff && !mIsOn)
		return;
	if (mpTransformComponent != nullptr && mpTexture != nullptr)
	{
		GameObject* pParent{ (GameObject*)mpTransformComponent->GetGameObject()->GetParent() };
		Vec2<int> pos{};
		if (pParent != nullptr)
			pos = pParent->GetModelComponent<TransformModelComponent>()->GetPos();
		pos += mpTransformComponent->GetPos();
		if (mIsSprite)
			pos.SetX((pos.GetX() / 16) * 16);
		if (mSize.GetX() == 0)
			mpEngine->GetRenderer()->RenderTexture(*mpTexture, pos);
		else
			mpEngine->GetRenderer()->RenderTexture(*mpTexture, Vec2<int>{ mSize.GetX() * mIndex, 0 }, mSize, pos);
	}
}

void RenderViewComponent::SetTransformComponent(TransformModelComponent* pTransformComponent)
{
	mpTransformComponent = pTransformComponent;
}

void RenderViewComponent::SetTexture(const std::string& file)
{
	mpTexture = mpEngine->GetResourceManager()->LoadTexture(file, mpEngine->GetRenderer());
}

// When Texture2D is used, we don't remove the old one from ResourceManager
// as it might be used for other RenderComponents
void RenderViewComponent::SetTexture(Texture2D* pTexture)
{
	mpTexture = pTexture;
}

Texture2D* RenderViewComponent::GetTexture()
{
	return mpTexture;
}

void RenderViewComponent::SetSize(int width, int height)
{
	mSize.SetXY(width, height);
}

void RenderViewComponent::SetIndex(int index)
{
	mIndex = index;
}

void RenderViewComponent::SetType(int type)
{
	mType = type;
}

void RenderViewComponent::SetAnimation(float delay, int startIndex, int stopIndex)
{
	mDelay = delay;
	mCurrDelay = delay;
	mStartIndex = startIndex;
	mIndex = startIndex;
	mStopIndex = stopIndex;
	mIsAnimating = true;
}

Texture2D* RenderViewComponent::SetTexture(SDL_Texture* pSDLTexture)
{
	mpTexture = mpEngine->GetResourceManager()->CreateTexture(pSDLTexture);
	return mpTexture;
}

// When SDL_Texture is used, it's a new one, so we remove the old
// Removing the old is mainly used for changing text textures
// as this is way too confusing, I changed this to ReplaceTexture
Texture2D* RenderViewComponent::ReplaceTexture(SDL_Texture* pSDLTexture)
{
	if (mpTexture != nullptr)
		mpEngine->GetResourceManager()->RemoveTexture(mpTexture);
	mpTexture = mpEngine->GetResourceManager()->CreateTexture(pSDLTexture);
	return mpTexture;
}

void RenderViewComponent::SetIsSprite(bool isSprite)
{
	mIsSprite = isSprite;
}

void RenderViewComponent::SetIsOnOff(bool isOnOff, float onOffDelay)
{
	mIsOnOff = isOnOff;
	mOnOffDelay = onOffDelay;
	mIsOn = !isOnOff;
}
