#include "pch.h"
#include "LevelComponent.h"
#include "BufferManager.h"
#include "BufferBubble.h"
#include "Avatar.h"
#include "../Engine/GameObject.h"
#include "../Engine/ColorRGBA8.h"

using namespace ieg;

const int LevelComponent::mpAvatarMax{ 2 };

LevelComponent::LevelComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
	, mpLevelPalette{ new ColorRGBA8[BufferBubble::GetPaletteColorCount()] }
	, mpGOAvatars{}
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	BufferManager* pBufferManager{ va_arg(vaList, BufferManager*) };
	ColorRGBA8* pLevelPalette{ va_arg(vaList, ColorRGBA8*) };
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };

	std::memcpy(mpLevelPalette, pLevelPalette, sizeof(ColorRGBA8) * BufferBubble::GetPaletteColorCount());
	Avatar* pAvatar{ new Avatar{ pEngine, pScene, pBufferManager, mpLevelPalette, AvatarType::Bub } };
	mpGOAvatars.push_back(pAvatar->GetGameObject());
	delete pAvatar;
	pAvatar = new Avatar{ pEngine, pScene, pBufferManager, mpLevelPalette, AvatarType::Bob };
	mpGOAvatars.push_back(pAvatar->GetGameObject());
	delete pAvatar;
}

LevelComponent::~LevelComponent()
{
	delete[] mpLevelPalette;
}

void LevelComponent::Update(const float deltaTime)
{
	(deltaTime);
}
