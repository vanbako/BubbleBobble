#include "pch.h"
#include "BubbleManager.h"
#include "BubbleComponent.h"
#include "HudComponent.h"
#include "Bubble.h"
#include "AvatarManager.h"

using namespace ieg;

BubbleManager::BubbleManager()
	: mpGOBubbles{}
{
}

void BubbleManager::CreateBubbles(Minigin* pEngine, BufferManager* pBufferManager, Scene* pScene, ColorRGBA8* pPalette)
{
	if (mpGOBubbles.size() != 0)
		return;
	for (int avatar{ 0 }; avatar < AvatarManager::GetAvatarMax(); ++avatar)
	{
		mpGOBubbles.push_back(Bubble::CreateBubble(pEngine, pScene, pBufferManager, pPalette, BubbleType(avatar)));
		GameObject* pGOBubble{ mpGOBubbles.back() };
		for (int bubble{ 1 }; bubble < mpBubblesPerAvatarMax; ++bubble)
			mpGOBubbles.push_back(Bubble::CopyBubble(pEngine, pGOBubble));
	}
}

void BubbleManager::Init(GameObject* pGOLevel)
{
	for (int bubble{ 0 }; bubble < AvatarManager::GetAvatarMax() * mpBubblesPerAvatarMax; ++bubble)
	{
		mpGOBubbles[bubble]->GetModelComponent<BubbleComponent>()->SetLevel(pGOLevel);
		mpGOBubbles[bubble]->SetIsActive(false);
	}
}

void BubbleManager::DeactivateAll()
{
	for (int bubble{ 0 }; bubble < AvatarManager::GetAvatarMax() * mpBubblesPerAvatarMax; ++bubble)
		mpGOBubbles[bubble]->SetIsActive(false);
}

void BubbleManager::FireBubble(AvatarType avatarType, const Vec2<int>& pos, bool isFiringLeft)
{
	for (int bubble{ int(avatarType) * mpBubblesPerAvatarMax }; bubble < (int(avatarType) + 1) * mpBubblesPerAvatarMax; ++bubble)
	{
		GameObject* pBubble{ mpGOBubbles[bubble] };
		if (!pBubble->IsActive())
		{
			pBubble->GetModelComponent<BubbleComponent>()->SetCaptureState();
			pBubble->GetModelComponent<BubbleComponent>()->SetIsFiringLeft(isFiringLeft);
			pBubble->GetModelComponent<TransformModelComponent>()->SetPos(pos);
			pBubble->GetModelComponent<TransformModelComponent>()->Switch();
			pBubble->SetIsActive(true);
			break;
		}
	}
}

ColliderModelComponent* BubbleManager::GetCollider()
{
	if (mpGOBubbles.size() == 0)
		return nullptr;
	return mpGOBubbles[0]->GetModelComponent<ColliderModelComponent>();
}

GameObject* BubbleManager::GetNextActiveBubble(GameObject* pGOBubble)
{
	if (pGOBubble == nullptr)
		return GetFirstActiveBubble();
	int bubble1{ -1 };
	for (int i{ 0 }; i < AvatarManager::GetAvatarMax() * mpBubblesPerAvatarMax; ++i)
		if (mpGOBubbles[i]->IsActive() && mpGOBubbles[i] == pGOBubble)
		{
			bubble1 = i;
			break;
		}
	if (bubble1 == -1)
		return nullptr;
	int bubble2{ -1 };
	for (int i{ bubble1 + 1 }; i < AvatarManager::GetAvatarMax() * mpBubblesPerAvatarMax; ++i)
		if (mpGOBubbles[i]->IsActive())
		{
			bubble2 = i;
			break;
		}
	if (bubble2 == -1)
		return nullptr;
	return mpGOBubbles[bubble2];
}

GameObject* BubbleManager::GetFirstActiveBubble()
{
	int bubble{ -1 };
	for (int i{ 0 }; i < AvatarManager::GetAvatarMax() * mpBubblesPerAvatarMax; ++i)
		if (mpGOBubbles[i]->IsActive())
		{
			bubble = i;
			break;
		}
	if (bubble == -1)
		return nullptr;
	return mpGOBubbles[bubble];
}
