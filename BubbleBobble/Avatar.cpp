#include "pch.h"
#include "Avatar.h"
#include "BufferManager.h"
#include "BufferAsprites.h"
#include "AvatarComponent.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "JumpCommand.h"
#include "FireCommand.h"

using namespace ieg;

const std::string Avatar::mInputFile{ "Avatar.txt" };
const int Avatar::mWidth{ 32 };
const int Avatar::mHeight{ 16 };
const int Avatar::mCount{ 16 };

GameObject* Avatar::CreateAvatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, ColorRGBA8* pPalette, AvatarType avatarType)
{
	BufferAsprites* pAsprites{ (BufferAsprites*)pBufferManager->GetBuffer(EnumBuffer::Asprites) };

	GameObject* pGOAvatar{ pScene->CreateObject<GameObject>(Order::front) };
	TransformModelComponent* pTransformComponent{ pGOAvatar->CreateModelComponent<TransformModelComponent>(pEngine) };
	RenderViewComponent* pRenderComponent{ pGOAvatar->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	pRenderComponent->SetIsSprite(true);
	AvatarComponent* pAvatarComponent{ pGOAvatar->CreateModelComponent<AvatarComponent>(pEngine, pObjectsManager) };
	pAvatarComponent->SetAvatarType(avatarType);
	pGOAvatar->CreateModelComponent<ColliderModelComponent>(pEngine, Vec2<int>{ 0, 8 }, Vec2<int>{ 15, 7 });

	InputAction* pInputAction{ pScene->GetInputManager()->CreateInputAction() };
	if (avatarType == AvatarType::Bub)
		pInputAction->LoadInput(mInputFile, "bubleft", VK_LEFT, 0);
	else
		pInputAction->LoadInput(mInputFile, "bobleft", 0, XINPUT_GAMEPAD_DPAD_LEFT);
	pInputAction->CreateAndSetCommand<LeftCommand>();
	pInputAction->SetActor(pAvatarComponent);

	pInputAction = pScene->GetInputManager()->CreateInputAction();
	if (avatarType == AvatarType::Bub)
		pInputAction->LoadInput(mInputFile, "bubright", VK_RIGHT, 0);
	else
		pInputAction->LoadInput(mInputFile, "bobright", 0, XINPUT_GAMEPAD_DPAD_RIGHT);
	pInputAction->CreateAndSetCommand<RightCommand>();
	pInputAction->SetActor(pAvatarComponent);

	pInputAction = pScene->GetInputManager()->CreateInputAction();
	if (avatarType == AvatarType::Bub)
		pInputAction->LoadInput(mInputFile, "bubup", VK_UP, 0);
	else
		pInputAction->LoadInput(mInputFile, "bobup", 0, XINPUT_GAMEPAD_DPAD_UP);
	pInputAction->CreateAndSetCommand<JumpCommand>();
	pInputAction->SetActor(pAvatarComponent);

	pInputAction = pScene->GetInputManager()->CreateInputAction();
	if (avatarType == AvatarType::Bub)
		pInputAction->LoadInput(mInputFile, "bubfire", VK_SPACE, 0);
	else
		pInputAction->LoadInput(mInputFile, "bobfire", 0, XINPUT_GAMEPAD_A);
	pInputAction->CreateAndSetCommand<FireCommand>();
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
	SDL_FreeSurface(pSurface);
	pRenderComponent->SetTexture(pSDLTexture);
	pRenderComponent->SetSize(mWidth, mHeight);
	if (avatarType == AvatarType::Bub)
		pRenderComponent->SetIndex(0);
	else
		pRenderComponent->SetIndex(15);

	delete[] pPixels;
	return pGOAvatar;
}

void Avatar::DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc)
{
	const int
		width{ BufferAsprites::GetWidth() },
		height{ BufferAsprites::GetHeight() };
	for (int row{ 0 }; row < height; ++row)
		memcpy(&pPixels[row * mCount * mWidth + (loc % width) * mWidth + (loc / width) * mCount * mWidth * height], &pSprite[offset * width * height + row * width], width * sizeof(ColorRGBA8));
}
