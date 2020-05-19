#include "pch.h"
#include "LevelComponent.h"
#include "AvatarComponent.h"
#include "HudComponent.h"
#include "HudObserver.h"
#include "Level.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Avatar.h"
#include "NpcComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/Scene.h"
#include "../Engine/ObsSubject.h"

using namespace ieg;

LevelComponent::LevelComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpLayout{ new char[Level::GetBlockCount()] }
	, mpEnemyData{ new char[Level::GetEnemyDataBytes()] }
	, mpPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpHudComponent{ nullptr }
	, mTest{ 15.f }
	, mpObsSubject{ new ObsSubject{} }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	BufferManager* pBufferManager{ va_arg(vaList, BufferManager*) };
	(pBufferManager);
	ColorRGBA8* pLevelPalette{ va_arg(vaList, ColorRGBA8*) };
	char* pLayout{ va_arg(vaList, char*) };
	char* pEnemyData{ va_arg(vaList, char*) };
	mpHudComponent = va_arg(vaList, HudComponent*);
	va_end(args);

	std::memcpy(mpPalette, pLevelPalette, sizeof(ColorRGBA8)* BufferBubble::GetPaletteColorCount());
	std::memcpy(mpLayout, pLayout, Level::GetBlockCount());
	std::memcpy(mpEnemyData, pEnemyData, Level::GetEnemyDataBytes());
	mpHudComponent->InitGameObjects(mpGameObject);
	// NPC data from Bdata
	//  byte1           byte2           byte3
	//  7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0
	// |Column   |Type |Row      |Bools  | |Wait Time   0|
	char* pLoop{ mpEnemyData };
	while (pLoop[0] != char(0))
	{
		int npcType{ int(pLoop[0] & 0x07) };
		Vec2<int> pos{ int(pLoop[0] & 0xf8), int(pLoop[1] & 0xf8) };
		int wait{ int((pLoop[2] & 0x3f) << 1) };
		mpHudComponent->SpawnNpc(NpcType(npcType), pos, wait);
		pLoop += 3;
	}
}

LevelComponent::~LevelComponent()
{
	delete mpObsSubject;
	delete[] mpEnemyData;
	delete[] mpPalette;
	delete[] mpLayout;
}

void LevelComponent::Update(const float deltaTime)
{
	(deltaTime);
	// Temporary end level after x seconds
	mTest -= deltaTime;
	if (mTest <= 0.f)
		mpObsSubject->Notify(typeid(this).hash_code(), int(LevelEvent::End), 0);
	// End temporary
}

ObsSubject* LevelComponent::GetObsSubject()
{
	return mpObsSubject;
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
