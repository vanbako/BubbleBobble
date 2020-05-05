#include "pch.h"
#include "LevelComponent.h"
#include "AvatarComponent.h"
#include "HudComponent.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Avatar.h"
#include "../Engine/GameObject.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/Scene.h"

using namespace ieg;

LevelComponent::LevelComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpLayout{ new char[Level::GetBlockCount()] }
	, mpPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpHudComponent{ nullptr }
	, mppGOBubbles{ nullptr }
	, mppGOAvatars{ nullptr }
	, mTest{ 10.f }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	BufferManager* pBufferManager{ va_arg(vaList, BufferManager*) };
	(pBufferManager);
	ColorRGBA8* pLevelPalette{ va_arg(vaList, ColorRGBA8*) };
	char* pLayout{ va_arg(vaList, char*) };
	mppGOAvatars = va_arg(vaList, GameObject**);
	mppGOBubbles = va_arg(vaList, GameObject**);
	mpHudComponent = va_arg(vaList, HudComponent*);
	va_end(args);

	std::memcpy(mpPalette, pLevelPalette, sizeof(ColorRGBA8)* BufferBubble::GetPaletteColorCount());
	std::memcpy(mpLayout, pLayout, Level::GetBlockCount());
	mppGOAvatars[0]->GetModelComponent<AvatarComponent>()->SetLevel(mpGameObject);
	mppGOAvatars[0]->SetIsActive(true);
	mppGOAvatars[1]->GetModelComponent<AvatarComponent>()->SetLevel(mpGameObject);
	mppGOAvatars[1]->SetIsActive(true);
}

LevelComponent::~LevelComponent()
{
	delete[] mpPalette;
	delete[] mpLayout;
}

void LevelComponent::Update(const float deltaTime)
{
	(deltaTime);
	mTest -= deltaTime;
	if (mTest <= 0.f)
	{
		mpHudComponent->EndLevel();
		mppGOAvatars[0]->SetIsActive(false);
		mppGOAvatars[1]->SetIsActive(false);
	}
}

unsigned short LevelComponent::CheckAvatarCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
{
	if (pTransform == nullptr || pCollider == nullptr) return false;
	const Vec2<int> pos{
		pTransform->GetNewPos().GetX() + pCollider->GetRelPos().GetX(),
		pTransform->GetNewPos().GetY() + pCollider->GetRelPos().GetY()
	};
	const Vec2<int>& size{ pCollider->GetSize() };
	unsigned short collision{ 0 };
	if (CheckCollisionPos(pos.GetX(), pos.GetY())) { collision |= 10; };
	if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY())) { collision |= 6; };
	if (CheckCollisionPos(pos.GetX(), pos.GetY() + size.GetY() - 8))
	{
		if (CheckCollisionPos(pos.GetX(), pos.GetY() + size.GetY())) { collision |= 8; };
	}
	else
		if (CheckCollisionPos(pos.GetX(), pos.GetY() + size.GetY())) { collision |= 9; };
	if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY() + size.GetY() - 8))
	{
		if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY() + size.GetY())) { collision |= 4; };
	}
	else
		if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY() + size.GetY())) { collision |= 5; };
	if (CheckCollisionPos(pos.GetX() + size.GetX() / 2, pos.GetY() + size.GetY() - 8))
	{
		if (CheckCollisionPos(pos.GetX() + size.GetX() / 2, pos.GetY() + size.GetY())) { collision |= 4; };
	}
	else
		if (CheckCollisionPos(pos.GetX() + size.GetX() / 2, pos.GetY() + size.GetY())) { collision |= 5; };
	return collision;
}

bool LevelComponent::CheckCollisionPos(const int x, const int y)
{
	if (x < 0 || x > 255) return false;
	if (y < 8 || y > 199) return false;

	if (mpLayout[x / 8 + y / 8 * 32] != 0)
		return true;
	else
		return false;
}
