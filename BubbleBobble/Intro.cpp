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
#include <SDL.h>

using namespace ieg;

Intro::Intro(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mpPixels{ new ColorRGBA8[320 * 200] }
	, mpColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpStartCommand{ new StartCommand{} }
{
	mpGameObject = mpScene->CreateObject<GameObject>(pEngine->GetResourceManager());
	TransformComponent* pTransformComponent{ mpGameObject->CreateComponent<TransformComponent>(0) };
	pTransformComponent->SetPosition(0.f, 0.f, 0.f);
	RenderComponent* pRenderComponent{ mpGameObject->CreateComponent<RenderComponent>(1, pEngine->GetRenderer()) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	IntroComponent* pIntroComponent{ mpGameObject->CreateComponent<IntroComponent>(0) };
	pIntroComponent->SetSceneManager(mpEngine->GetSceneManager());
	pIntroComponent->SetStartScene(pGameScene);
	InputAction* pInputAction{ pScene->GetInputManager()->CreateInputAction() };
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
		320,
		200,
		sizeof(ColorRGBA8),
		320 * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	Texture2D* pTexture2D{ new Texture2D{ pTexture } };
	pEngine->GetResourceManager()->AddTexture(pTexture2D);
	pRenderComponent->SetTexture(pTexture2D);
}

Intro::~Intro()
{
	delete[] mpPixels;
	delete[] mpColorPalette;
	delete mpStartCommand;
}
