#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdarg>
#include <string>
#include <exception>
#include <thread>
#include <atomic>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <SDL.h>

#include "../Engine/Audio.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/ColorRGBA8.h"
#include "../Engine/Command.h"
#include "../Engine/CtrlComponent.h"
#include "../Engine/FileLogger.h"
#include "../Engine/GameObject.h"
#include "../Engine/InputAction.h"
#include "../Engine/InputManager.h"
#include "../Engine/Minigin.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/Observer.h"
#include "../Engine/ObsSubject.h"
#include "../Engine/RegularAudio.h"
#include "../Engine/Renderer.h"
#include "../Engine/RenderViewComponent.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Scene.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/State.h"
#include "../Engine/Texture2D.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/Vec2.h"
