#include "pch.h"
#include "Avatar.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "AvatarComponent.h"
#include "LeftCommand.h"
#include "RightCommand.h"
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

const int Avatar::mWidth{ 32 };
const int Avatar::mHeight{ 16 };
const int Avatar::mCount{ 16 };

Avatar::Avatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, GameObject* pLevel, ColorRGBA8* pPalette, AvatarType avatarType)
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	mpGOAvatar = pScene->CreateObject<GameObject>();
	TransformModelComponent* pTransformComponent{ mpGOAvatar->CreateModelComponent<TransformModelComponent>(pEngine) };
	if (avatarType == AvatarType::Bub)
		pTransformComponent->SetPos(16, 176);
	else
		pTransformComponent->SetPos(208, 176);
	RenderViewComponent* pRenderComponent{ mpGOAvatar->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	AvatarComponent* pAvatarComponent{ mpGOAvatar->CreateModelComponent<AvatarComponent>(pEngine, pLevel) };
	mpGOAvatar->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 8, 0 }, Vec2<int>{ 16, 16 });
	InputAction* pInputAction{ pScene->GetInputManager()->CreateInputAction() };
	if (avatarType == AvatarType::Bub)
		pInputAction->SetKeyboardKey(VK_LEFT);
	else
		pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_DPAD_LEFT);
	pInputAction->CreateAndSetCommand<LeftCommand>();
	pInputAction->SetActor(pAvatarComponent);
	pInputAction = pScene->GetInputManager()->CreateInputAction();
	if (avatarType == AvatarType::Bub)
		pInputAction->SetKeyboardKey(VK_RIGHT);
	else
		pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_DPAD_RIGHT);
	pInputAction->CreateAndSetCommand<RightCommand>();
	pInputAction->SetActor(pAvatarComponent);

	ColorRGBA8* pPixels{ new ColorRGBA8[mCount * mWidth * mHeight] };

	ColorRGBA8* pSprite{ new ColorRGBA8[mCount * BufferAsprites::GetWidth() * BufferAsprites::GetHeight()] };
	if (avatarType == AvatarType::Bub)
		pAsprites->GetSprites(pSprite, 16, Sprite::Bub, pPalette);
	else
		pAsprites->GetSprites(pSprite, 16, Sprite::Bob, pPalette);
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
	if (avatarType == AvatarType::Bub)
		pRenderComponent->SetIndex(0);
	else
		pRenderComponent->SetIndex(15);

	delete[] pPixels;
}

GameObject* Avatar::GetGameObject()
{
	return mpGOAvatar;
}

void Avatar::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
