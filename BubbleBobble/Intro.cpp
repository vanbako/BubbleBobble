#include "pch.h"
#include "Intro.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "BufferApic.h"
#include "ColorRGBA8.h"
#include "IntroComponent.h"
#include "StartCommand.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/InputAction.h"
#include "../Engine/ServiceLocator.h"
#include <SDL.h>

using namespace ieg;

const size_t Intro::mWidth{ 320 };
const size_t Intro::mHeight{ 200 };

Intro::Intro(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mpPixels{ new ColorRGBA8[mWidth * mHeight] }
	, mpColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpStartCommand{ new StartCommand{} }
	, mpTexture2D{ nullptr }
{

	mpGameObject = mpScene->CreateObject<GameObject>();
	TransformComponent* pTransformComponent{ mpGameObject->CreateComponent<TransformComponent>(mpEngine) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderComponent* pRenderComponent{ mpGameObject->CreateComponent<RenderComponent>(mpEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	IntroComponent* pIntroComponent{ mpGameObject->CreateComponent<IntroComponent>(mpEngine) };
	pIntroComponent->SetStartScene(pGameScene);
	InputAction* pInputAction{ mpScene->GetInputManager()->CreateInputAction() };
	pInputAction->SetKeyboardKey(VK_SPACE);
	pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_START);
	pInputAction->SetCommand(mpStartCommand);
	pInputAction->SetActor(pIntroComponent);

	BufferBubble* pBubble{ (BufferBubble*)mpBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferApic* pApic{ (BufferApic*)mpBufferManager->GetBuffer(EnumBuffer::Apic) };

	pBubble->GetIntroColors(mpColorPalette);
	pApic->GetPic(mpPixels, mpColorPalette);
	
	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		mpPixels,
		mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(mpEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	mpTexture2D = pRenderComponent->SetTexture(pSDLTexture);
}

Intro::~Intro()
{
	mpEngine->GetResourceManager()->RemoveTexture(mpTexture2D);
	delete[] mpPixels;
	delete[] mpColorPalette;
	delete mpStartCommand;
}
