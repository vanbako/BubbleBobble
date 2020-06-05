#include "pch.h"
#include "AvatarManager.h"
#include "Avatar.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/Observer.h"
#include "../Engine/ObsSubject.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const Vec2<int> AvatarManager::mpAvatarInitialPos[mpAvatarMax]{
	Vec2<int>{ 24, 176 },
	Vec2<int>{ 208, 176 }
};

AvatarManager::AvatarManager()
	: mpGOAvatars{}
{
}

void AvatarManager::CreateAvatars(Minigin* pEngine, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, Scene* pScene, ColorRGBA8* pPalette, Observer* pObserver)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mpGOAvatars.push_back(Avatar::CreateAvatar(pEngine, pScene, pBufferManager, pObjectsManager, pPalette, AvatarType(avatar)));
		GameObject* pGOAvatar{ mpGOAvatars.back() };
		pGOAvatar->GetModelComponent<AvatarComponent>()->GetObsSubject()->AddObserver(pObserver);
		pGOAvatar->SetIsActive(false);
	}
}

void AvatarManager::Init(GameObject* pGOLevel)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mpGOAvatars[avatar]->GetModelComponent<AvatarComponent>()->SetLevel(pGOLevel);
		mpGOAvatars[avatar]->GetModelComponent<TransformModelComponent>()->SetPos(mpAvatarInitialPos[avatar]);
		mpGOAvatars[avatar]->GetModelComponent<TransformModelComponent>()->Switch();
		mpGOAvatars[avatar]->SetIsActive(true);
	}
}

void AvatarManager::DeactivateAll()
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
		mpGOAvatars[avatar]->SetIsActive(false);
}
