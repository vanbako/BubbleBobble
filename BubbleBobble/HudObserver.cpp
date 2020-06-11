#include "pch.h"
#include "HudObserver.h"
#include "HudComponent.h"
#include "LevelComponent.h"
#include "AvatarComponent.h"
#include "NpcComponent.h"

using namespace ieg;

HudObserver::HudObserver(HudComponent* pHudComponent)
	: mpHudComponent{ pHudComponent }
{
}

void HudObserver::OnNotify(size_t subject, int event, int value)
{
	(value);
	if (subject == typeid(LevelComponent*).hash_code())
		switch (LevelEvent(event))
		{
		case LevelEvent::End:
			mpHudComponent->NextLevel();
			break;
		};
	if (subject == typeid(AvatarComponent*).hash_code())
		switch (AvatarEvent(event))
		{
		case AvatarEvent::Score:
			mpHudComponent->DeltaScore(value);
			break;
		case AvatarEvent::Die:
			mpHudComponent->AvatarDie(value);
			break;
		};
	if (subject == typeid(NpcComponent*).hash_code())
		switch (NpcEvent(event))
		{
		case NpcEvent::Die:
			break;
		};
}
