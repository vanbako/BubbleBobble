#include "pch.h"
#include "Npc.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "NpcComponent.h"
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

GameObject* Npc::CreateNpc(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, GameObject* pLevel, ColorRGBA8* pPalette, NpcType npcType, int col, int row)
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	GameObject* pGONpc{ pScene->CreateObject<GameObject>() };
	TransformModelComponent* pTransformComponent{ pGONpc->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(col, row);
	pTransformComponent->Switch();
	RenderViewComponent* pRenderComponent{ pGONpc->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	NpcComponent* pNpcComponent{ pGONpc->CreateModelComponent<NpcComponent>(pEngine, pLevel) };
	(pNpcComponent);
	pGONpc->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 8 }, Vec2<int>{ 15, 7 });

	ColorRGBA8* pPixels{ new ColorRGBA8[mCount * mWidth * mHeight] };

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	switch (npcType)
	{
	case NpcType::ZenChan:
		pAsprites->GetSprites(pSprite, 16, Sprite::ZenChan, pPalette);
		break;
	case NpcType::Hidegons:
		pAsprites->GetSprites(pSprite, 16, Sprite::Hidegons, pPalette);
		break;
	case NpcType::Banebou:
		pAsprites->GetSprites(pSprite, 16, Sprite::Banebou, pPalette);
		break;
	case NpcType::PulPul:
		pAsprites->GetSprites(pSprite, 8, Sprite::PulPul, pPalette);
		break;
	case NpcType::Monsta:
		pAsprites->GetSprites(pSprite, 16, Sprite::Monsta, pPalette);
		break;
	case NpcType::Drunk:
		pAsprites->GetSprites(pSprite, 16, Sprite::Drunk, pPalette);
		break;
	case NpcType::Maita:
		pAsprites->GetSprites(pSprite, 16, Sprite::Maita, pPalette);
		break;
	case NpcType::Invader:
		pAsprites->GetSprites(pSprite, 8, Sprite::Invader, pPalette);
		break;
	}
	for (int sprite{ 0 }; sprite < mCount; ++sprite)
		DrawSprite(pSprite, pPixels, sprite, sprite);
	delete[] pSprite;

	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		mCount * mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mCount * mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(mWidth, mHeight);
	pRenderComponent->SetIndex(0);

	delete[] pPixels;
	return pGONpc;
}

void Npc::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
