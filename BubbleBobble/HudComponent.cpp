#include "pch.h"
#include "HudComponent.h"
#include "BufferManager.h"
#include "Level.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"

using namespace ieg;

HudComponent::HudComponent(GameObject* pGameObject, Minigin* pEngine,...)
	: ModelComponent(pGameObject, pEngine)
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	BufferManager* pBufferManager{ va_arg(vaList, BufferManager*) };
	va_end(args);
	Scene* pScene{ mpGameObject->GetScene() };
	Level* pLevel{ new Level{ 7, pEngine, pScene, pBufferManager } };
	mpGOLevel = pLevel->GetGameObject();
	delete pLevel;
}

HudComponent::~HudComponent()
{
}

void HudComponent::Update(const float deltaTime)
{
	(deltaTime);
}
