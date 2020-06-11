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
#include "CandyComponent.h"
#include "ObjectsManager.h"
#include "AvatarManager.h"
#include "BubbleManager.h"
#include "NpcManager.h"
#include "CandyManager.h"
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
	, mpObjectsManager{ nullptr }
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
	mpObjectsManager = va_arg(vaList, ObjectsManager*);
	va_end(args);

	std::memcpy(mpPalette, pLevelPalette, sizeof(ColorRGBA8) * BufferBubble::GetPaletteColorCount());
	std::memcpy(mpLayout, pLayout, Level::GetBlockCount());
	std::memcpy(mpEnemyData, pEnemyData, Level::GetEnemyDataBytes());
	mpObjectsManager->InitGameObjects(mpGameObject);
	// NPC data from Bdata
	//  byte0           byte1           byte2
	//  7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0
	// |Column   |Type |Row      |Bools  | |Wait Time   0|
	char* pLoop{ mpEnemyData };
	while (pLoop[0] != char(0))
	{
		int npcType{ int(pLoop[0] & 0x07) };
		Vec2<int> pos{ int(pLoop[0] & 0xf8), int(pLoop[1] & 0xf8) - 32 };
		int wait{ int((pLoop[2] & 0x3f) << 1) };
		bool isLookingLeft{ ((pLoop[2] & 0x80) > 0) ? true : false};
		mpObjectsManager->GetNpcManager()->SpawnNpc(NpcType(npcType), pos, isLookingLeft, wait);
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
}

ObsSubject* LevelComponent::GetObsSubject()
{
	return mpObsSubject;
}

// TODO: change unsigned short to bitset

unsigned short LevelComponent::CheckAvatarCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
{
	if (pTransform == nullptr || pCollider == nullptr) return false;
	const Vec2<int> pos{
		pTransform->GetNewPos().GetX() + pCollider->GetRelPos().GetX(),
		pTransform->GetNewPos().GetY() + pCollider->GetRelPos().GetY()
	};
	const Vec2<int>& size{ pCollider->GetSize() };
	unsigned short collision{ 0 };
	// Left Top: 1010
	if (CheckCollisionPos(pos.GetX(), pos.GetY())) { collision |= 10; };
	// Right Top: 0110
	if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY())) { collision |= 6; };
	if (CheckCollisionPos(pos.GetX(), pos.GetY() + size.GetY() - 8))
	{
		// Left Bottom&OneUp: 1000
		if (CheckCollisionPos(pos.GetX(), pos.GetY() + size.GetY())) { collision |= 8; };
	}
	else
		// Left Bottom: 1001
		if (CheckCollisionPos(pos.GetX(), pos.GetY() + size.GetY())) { collision |= 9; };
	if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY() + size.GetY() - 8))
	{
		// Right Bottom&OneUp: 0100
		if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY() + size.GetY())) { collision |= 4; };
	}
	else
		// Right Bottom: 0101
		if (CheckCollisionPos(pos.GetX() + size.GetX(), pos.GetY() + size.GetY())) { collision |= 5; };
	if (CheckCollisionPos(pos.GetX() + size.GetX() / 2, pos.GetY() + size.GetY() - 8))
	{
		// Middle Bottom&OneUp: 0100
		if (CheckCollisionPos(pos.GetX() + size.GetX() / 2, pos.GetY() + size.GetY())) { collision |= 4; };
	}
	else
		// Middle Bottom: 0101
		if (CheckCollisionPos(pos.GetX() + size.GetX() / 2, pos.GetY() + size.GetY())) { collision |= 5; };
	return collision;
}

unsigned short LevelComponent::CheckRectangleCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
{
	unsigned short collision{ 0 };
	if (pTransform == nullptr || pCollider == nullptr) return false;
	const Vec2<int> posX{
		pTransform->GetNewPos().GetX() + pCollider->GetRelPos().GetX(),
		pTransform->GetPos().GetY() + pCollider->GetRelPos().GetY()
	};
	const Vec2<int> posY{
		pTransform->GetPos().GetX() + pCollider->GetRelPos().GetX(),
		pTransform->GetNewPos().GetY() + pCollider->GetRelPos().GetY()
	};
	const Vec2<int>& size{ pCollider->GetSize() };
	// Left: 1000
	if (CheckCollisionPos(posX.GetX(), posX.GetY()) ||
		CheckCollisionPos(posX.GetX(), posX.GetY() + size.GetY() / 2) ||
		CheckCollisionPos(posX.GetX(), posX.GetY() + size.GetY())
		)
	{
		collision |= 8;
	};
	// Right: 0100
	if (CheckCollisionPos(posX.GetX() + size.GetX(), posX.GetY()) ||
		CheckCollisionPos(posX.GetX() + size.GetX(), posX.GetY() + size.GetY() / 2) ||
		CheckCollisionPos(posX.GetX() + size.GetX(), posX.GetY() + size.GetY())
		)
	{
		collision |= 4;
	};
	// Top: 0010
	if (CheckCollisionPos(posY.GetX(), posY.GetY()) ||
		CheckCollisionPos(posY.GetX() + size.GetX() / 2, posY.GetY()) ||
		CheckCollisionPos(posY.GetX() + size.GetX(), posY.GetY())
		)
	{
		collision |= 2;
	};
	// Bottom: 0001
	if (CheckCollisionPos(posY.GetX(), posY.GetY() + size.GetY()) ||
		CheckCollisionPos(posY.GetX() + size.GetX() / 2, posY.GetY() + size.GetY()) ||
		CheckCollisionPos(posY.GetX() + size.GetX(), posY.GetY() + size.GetY())
		)
	{
		collision |= 1;
	};
	return collision;
}

unsigned short LevelComponent::CheckRectanglePosCollision(const Vec2<int>& pos, ColliderModelComponent* pCollider)
{
	unsigned short collision{ 0 };
	if (pCollider == nullptr) return false;
	const Vec2<int> rPos{
		pos.GetX() + pCollider->GetRelPos().GetX(),
		pos.GetY() + pCollider->GetRelPos().GetY()
	};
	const Vec2<int>& size{ pCollider->GetSize() };
	// Left: 1000
	if (CheckCollisionPos(rPos.GetX(), rPos.GetY()) ||
		CheckCollisionPos(rPos.GetX(), rPos.GetY() + size.GetY() / 2) ||
		CheckCollisionPos(rPos.GetX(), rPos.GetY() + size.GetY())
		)
	{
		collision |= 8;
	};
	// Right: 0100
	if (CheckCollisionPos(rPos.GetX() + size.GetX(), rPos.GetY()) ||
		CheckCollisionPos(rPos.GetX() + size.GetX(), rPos.GetY() + size.GetY() / 2) ||
		CheckCollisionPos(rPos.GetX() + size.GetX(), rPos.GetY() + size.GetY())
		)
	{
		collision |= 4;
	};
	// Top: 0010
	if (CheckCollisionPos(rPos.GetX(), rPos.GetY()) ||
		CheckCollisionPos(rPos.GetX() + size.GetX() / 2, rPos.GetY()) ||
		CheckCollisionPos(rPos.GetX() + size.GetX(), rPos.GetY())
		)
	{
		collision |= 2;
	};
	// Bottom: 0001
	if (CheckCollisionPos(rPos.GetX(), rPos.GetY() + size.GetY()) ||
		CheckCollisionPos(rPos.GetX() + size.GetX() / 2, rPos.GetY() + size.GetY()) ||
		CheckCollisionPos(rPos.GetX() + size.GetX(), rPos.GetY() + size.GetY())
		)
	{
		collision |= 1;
	};
	return collision;
}

GameObject* LevelComponent::CheckNpcCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
{
	GameObject* pGONpc{ mpObjectsManager->GetNpcManager()->GetNextActiveNpc(nullptr) };
	while (pGONpc != nullptr)
	{
		if (pGONpc->GetModelComponent<ColliderModelComponent>()->DoesCollide(pGONpc->GetModelComponent<TransformModelComponent>(), pTransform, pCollider))
			return pGONpc;
		pGONpc = mpObjectsManager->GetNpcManager()->GetNextActiveNpc(pGONpc);
	}
	return nullptr;
}

GameObject* LevelComponent::CheckCandyCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
{
	GameObject* pGOCandy{ mpObjectsManager->GetCandyManager()->GetNextActiveCandy(nullptr) };
	while (pGOCandy != nullptr)
	{
		if (pGOCandy->GetModelComponent<ColliderModelComponent>()->DoesCollide(pGOCandy->GetModelComponent<TransformModelComponent>(), pTransform, pCollider))
			return pGOCandy;
		pGOCandy = mpObjectsManager->GetCandyManager()->GetNextActiveCandy(pGOCandy);
	}
	return nullptr;
}

bool LevelComponent::CheckBubbleNpcCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider)
{
	GameObject* pGONpc{ mpObjectsManager->GetNpcManager()->GetNextActiveNpc(nullptr) };
	while (pGONpc != nullptr)
	{
		if (pGONpc->GetModelComponent<ColliderModelComponent>()->DoesCollide(pGONpc->GetModelComponent<TransformModelComponent>(), pTransform, pCollider))
			return pGONpc->GetModelComponent<NpcComponent>()->Capture();
		pGONpc = mpObjectsManager->GetNpcManager()->GetNextActiveNpc(pGONpc);
	}
	return false;
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

void LevelComponent::SpawnAvatar(AvatarType avatarType)
{
	mpObjectsManager->GetAvatarManager()->Spawn(avatarType);
}

void LevelComponent::SpawnCandy(NpcType npcType, TransformModelComponent* pTransform)
{
	mpObjectsManager->GetCandyManager()->SpawnCandy(npcType, pTransform);
}

void LevelComponent::CheckLastNpc()
{
	if (mpObjectsManager->GetNpcManager()->GetNextActiveNpc(nullptr) == nullptr)
		mpObsSubject->Notify(typeid(this).hash_code(), int(LevelEvent::End), 0);
}
