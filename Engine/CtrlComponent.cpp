#include "pch.h"
#include "CtrlComponent.h"
#include "GameObject.h"

using namespace ieg;

CtrlComponent::CtrlComponent(GameObject* pGameObject, Minigin* pEngine)
	: mpGameObject{ pGameObject }
	, mpEngine{ pEngine }
	, mRunThread{ true }
	, mThread{}
	, mMutex{}
{
	mThread = std::thread{ [=]() { CtrlLoop(); } };
}

CtrlComponent::~CtrlComponent()
{
	mRunThread.store(false);
	if (mThread.joinable())
		mThread.join();
}

GameObject* CtrlComponent::GetGameObject()
{
	return mpGameObject;
}

bool CtrlComponent::Lock(std::chrono::duration<float> duration)
{
	return mMutex.try_lock_for(duration);
}

void CtrlComponent::Unlock()
{
	mMutex.unlock();
}

void CtrlComponent::CtrlLoop()
{
	std::chrono::duration<float> sleepTime{ 0.02f };
	std::chrono::duration<float> waitForLock{ 0.005f };
	while (mRunThread.load())
	{
		if (mpGameObject->IsActive() && mMutex.try_lock_for(waitForLock))
		{
			Update(sleepTime.count());
			mMutex.unlock();
		}
		std::this_thread::sleep_for(sleepTime);
	}
}
