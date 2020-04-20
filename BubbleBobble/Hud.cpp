#include "pch.h"
#include "Hud.h"
#include "ColorRGBA8.h"
#include "BufferAsprites.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Minigin.h"
#include "../Engine/Renderer.h"
#include "../Engine/Texture2D.h"
#include "../Engine/ResourceManager.h"

using namespace ieg;

Hud::Hud(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette)
	: mpEngine{ pEngine }
	, mpScene{ pScene }
	, mpBufferManager{ pBufferManager }
	, mpGameObject{ nullptr }
	, mpColorPalette{ new ColorRGBA8[16] }
{
	std::memcpy(mpColorPalette, pPalette, 16 * sizeof(ColorRGBA8));
}

Hud::~Hud()
{
	delete[] mpColorPalette;
}
