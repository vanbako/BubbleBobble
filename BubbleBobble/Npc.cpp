#include "pch.h"
#include "Npc.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "NpcComponent.h"
#include "NpcCtrlComponent.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "JumpCommand.h"
#include "../Engine/Minigin.h"
#include "../Engine/Scene.h"
#include "../Engine/Renderer.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include "../Engine/InputAction.h"
#include "../Engine/InputManager.h"
#include "../Engine/ColorRGBA8.h"
#include <SDL.h>

using namespace ieg;

const int Npc::mWidth{ 32 };
const int Npc::mHeight{ 16 };
const int Npc::mCount{ 16 };
const NpcData Npc::mNpcData[]{
	NpcData{ Sprite::ZenChan, true },
	NpcData{ Sprite::Hidegons, true },
	NpcData{ Sprite::Banebou, true },
	NpcData{ Sprite::PulPul, false },
	NpcData{ Sprite::Monsta, true },
	NpcData{ Sprite::Drunk, true },
	NpcData{ Sprite::Maita, true },
	NpcData{ Sprite::Invader, false }
};

GameObject* Npc::CreateNpc(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette)
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	GameObject* pGONpc{ pScene->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGONpc->CreateModelComponent<TransformModelComponent>(pEngine) };
	RenderViewComponent* pRenderComponent{ pGONpc->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	pGONpc->CreateModelComponent<NpcComponent>(pEngine);
	pGONpc->CreateCtrlComponent<NpcCtrlComponent>(pEngine);
	pGONpc->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 0 }, Vec2<int>{ 15, 15 });

	ColorRGBA8* pPixels{ new ColorRGBA8[int(NpcType::Count) * mCount * mWidth * mHeight] };

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	int spriteCount{ 16 };
	for (int npcType{ 0 }; npcType < int(NpcType::Count); ++npcType)
	{
		if (mNpcData[npcType].isLeftRightDiff)
			spriteCount = 16;
		else
			spriteCount = 8;
		std::memset(pSprite, 0, size_t(mCount) * size_t(BufferAsprites::GetWidth()) * size_t(BufferAsprites::GetHeight()) * sizeof(ColorRGBA8));
		pAsprites->GetSprites(pSprite, spriteCount, mNpcData[npcType].sprite, pPalette);
		for (int sprite{ 0 }; sprite < spriteCount; ++sprite)
			DrawSprite(pSprite, pPixels, sprite, npcType * mCount + sprite);
	}
	delete[] pSprite;

	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		int(NpcType::Count) * mCount * mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		int(NpcType::Count) * mCount * mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	// Debug
	//SDL_SaveBMP(pSurface, "Npcs.bmp");
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(mWidth, mHeight);
	pRenderComponent->SetIndex(0);

	delete[] pPixels;
	return pGONpc;
}

GameObject* Npc::CopyNpc(Minigin* pEngine, GameObject* pGONpc)
{
	GameObject* pGONpcCopy{ pGONpc->GetScene()->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGONpcCopy->CreateModelComponent<TransformModelComponent>(pEngine) };
	RenderViewComponent* pRenderComponent{ pGONpcCopy->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	pRenderComponent->SetTexture(pGONpc->GetViewComponent<RenderViewComponent>()->GetTexture());
	pRenderComponent->SetSize(mWidth, mHeight);
	pGONpcCopy->CreateModelComponent<NpcComponent>(pEngine);
	pGONpcCopy->CreateCtrlComponent<NpcCtrlComponent>(pEngine);
	pGONpcCopy->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 0 }, Vec2<int>{ 15, 15 });
	return pGONpcCopy;
}

void Npc::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(
			&pPixels[row * int(NpcType::Count) * mCount * mWidth + loc * mWidth],
			&pSprite[offset * width * height + row * width],
			width * sizeof(ColorRGBA8));
}
