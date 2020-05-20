#include "pch.h"
#include "BubbleManager.h"
#include "BubbleComponent.h"
#include "HudComponent.h"
#include "Bubble.h"
#include "AvatarManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"

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

void BubbleManager::FireBubble(const Vec2<int>& pos)
{
	for (int bubble{ 0 }; bubble < AvatarManager::GetAvatarMax() * mpBubblesPerAvatarMax; ++bubble)
	{
		GameObject* pBubble{ mpGOBubbles[bubble] };
		if (!pBubble->IsActive())
		{
			pBubble->SetIsActive(true);
			pBubble->GetModelComponent<TransformModelComponent>()->SetPos(pos);
			pBubble->GetModelComponent<TransformModelComponent>()->Switch();
			break;
		}
	}
}