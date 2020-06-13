#include "pch.h"
#include "AvatarManager.h"
#include "Avatar.h"
#include "AvatarComponent.h"

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
	GameObject* pGOAvatar{ nullptr };
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mpGOAvatars.push_back(Avatar::CreateAvatar(pEngine, pScene, pBufferManager, pObjectsManager, pPalette, AvatarType(avatar)));
		pGOAvatar = mpGOAvatars.back();
		pGOAvatar->GetModelComponent<AvatarComponent>()->GetObsSubject()->AddObserver(pObserver);
		pGOAvatar->SetIsActive(false);
	}
}

void AvatarManager::Init(GameObject* pGOLevel)
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
	{
		mpGOAvatars[avatar]->GetModelComponent<AvatarComponent>()->SetLevel(pGOLevel);
		TransformModelComponent* pTransform{ mpGOAvatars[avatar]->GetModelComponent<TransformModelComponent>() };
		pTransform->SetPos(mpAvatarInitialPos[avatar]);
		pTransform->Switch();
		mpGOAvatars[avatar]->SetIsActive(true);
		if ((AvatarType)avatar == AvatarType::Bob)
			pTransform->SetIsLookingLeft(true);
		else
			pTransform->SetIsLookingLeft(false);
	}
}

void AvatarManager::DeactivateAll()
{
	for (int avatar{ 0 }; avatar < mpAvatarMax; ++avatar)
		mpGOAvatars[avatar]->SetIsActive(false);
}

void AvatarManager::Spawn(AvatarType avatar)
{
	GameObject* pGOAvatar{ mpGOAvatars[int(avatar)] };
	TransformModelComponent* pTransform{ pGOAvatar->GetModelComponent<TransformModelComponent>() };
	pTransform->SetPos(mpAvatarInitialPos[int(avatar)]);
	pTransform->Switch();
	AvatarComponent* pAvatarComponent{ pGOAvatar->GetModelComponent<AvatarComponent>() };
	pAvatarComponent->SetStandingState();
	pAvatarComponent->SetInvincibleState();
	pAvatarComponent->SetReadyState();
	pGOAvatar->SetIsActive(true);
	if (avatar == AvatarType::Bob)
		pTransform->SetIsLookingLeft(true);
	else
		pTransform->SetIsLookingLeft(false);
}
