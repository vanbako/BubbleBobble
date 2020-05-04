#include "pch.h"
#include "LevelComponent.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Avatar.h"
#include "../Engine/GameObject.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const int LevelComponent::mpAvatarMax{ 2 };

LevelComponent::LevelComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpLayout{ new char[Level::GetBlockCount()] }
	, mpLevelPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpGOAvatars{}
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	BufferManager* pBufferManager{ va_arg(vaList, BufferManager*) };
	ColorRGBA8* pLevelPalette{ va_arg(vaList, ColorRGBA8*) };
	char* pLayout{ va_arg(vaList, char*) };
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };

	std::memcpy(mpLevelPalette, pLevelPalette, sizeof(ColorRGBA8)* BufferBubble::GetPaletteColorCount());
	std::memcpy(mpLayout, pLayout, Level::GetBlockCount());

	Avatar* pAvatar{ new Avatar{ pEngine, pScene, pBufferManager, pGameObject, mpLevelPalette, AvatarType::Bub } };
	mpGOAvatars.push_back(pAvatar->GetGameObject());
	delete pAvatar;
	pAvatar = new Avatar{ pEngine, pScene, pBufferManager, pGameObject, mpLevelPalette, AvatarType::Bob };
	mpGOAvatars.push_back(pAvatar->GetGameObject());
	delete pAvatar;
}

LevelComponent::~LevelComponent()
{
	delete[] mpLevelPalette;
	delete[] mpLayout;
}

void LevelComponent::Update(const float deltaTime)
{
	(deltaTime);
}

unsigned short LevelComponent::CheckCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
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

bool ieg::LevelComponent::CheckCollisionPos(const int x, const int y)
{
	if (x < 0 || x > 255) return false;
	if (y < 8 || y > 199) return false;

	if (mpLayout[x / 8 + y / 8 * 32] != 0)
		return true;
	else
		return false;
}
