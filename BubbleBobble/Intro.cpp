#include "pch.h"
#include "Intro.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "BufferApic.h"
#include "../Engine/ColorRGBA8.h"
#include "IntroComponent.h"
#include "Start1Command.h"
#include "Start2Command.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/InputAction.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include <SDL.h>

using namespace ieg;

const int Intro::mWidth{ 320 };
const int Intro::mHeight{ 200 };

GameObject* Intro::CreateIntro(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, Scene* pGameScene)
{
	GameObject* pGOIntro = pScene->CreateObject<GameObject>();
	TransformModelComponent* pTransformComponent{ pGOIntro->CreateModelComponent<TransformModelComponent>(pEngine) };
	pTransformComponent->SetPos(0, 0);
	RenderViewComponent* pRenderComponent{ pGOIntro->CreateViewComponent<RenderViewComponent>(pEngine) };
	pRenderComponent->SetTransformComponent(pTransformComponent);
	IntroComponent* pIntroComponent{ pGOIntro->CreateModelComponent<IntroComponent>(pEngine) };
	pIntroComponent->SetStartScene(pGameScene);

	InputAction* pInputAction{ pScene->GetInputManager()->CreateInputAction() };
	pInputAction->SetKeyboardKey('1');
	pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_START);
	pInputAction->CreateAndSetCommand<Start1Command>();
	pInputAction->SetActor(pIntroComponent);

	pInputAction = pScene->GetInputManager()->CreateInputAction();
	pInputAction->SetKeyboardKey('2');
	pInputAction->SetGamepadButtonCode(XINPUT_GAMEPAD_START);
	pInputAction->CreateAndSetCommand<Start1Command>();
	pInputAction->SetActor(pIntroComponent);

	BufferBubble* pBubble{ (BufferBubble*)pBufferManager->GetBuffer(EnumBuffer::Bubble) };
	BufferApic* pApic{ (BufferApic*)pBufferManager->GetBuffer(EnumBuffer::Apic) };

	ColorRGBA8* pPixels{ new ColorRGBA8[mWidth * mHeight] };
	ColorRGBA8* pColorPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] };

	pBubble->GetIntroColors(pColorPalette);
	pApic->GetPic(pPixels, pColorPalette);
	
	SDL_Surface* pSurface{
	SDL_CreateRGBSurfaceWithFormatFrom(
		pPixels,
		mWidth,
		mHeight,
		sizeof(ColorRGBA8),
		mWidth * sizeof(ColorRGBA8),
		SDL_PIXELFORMAT_RGBA32) };
	SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(pEngine->GetRenderer()->GetSDLRenderer(), pSurface) };
	pRenderComponent->SetTexture(pSDLTexture);

	delete[] pPixels;
	delete[] pColorPalette; 

	pGOIntro->SetIsActive(true);
	return pGOIntro;
}
