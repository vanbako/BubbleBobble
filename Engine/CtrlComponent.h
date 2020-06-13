#pragma once
#include <thread>
#include <atomic>
#include <mutex>

namespace ieg
{
	class Minigin;
	class GameObject;

	class CtrlComponent
	{
	public:
		explicit CtrlComponent(GameObject* pGameObject, Minigin* pEngine);
		virtual ~CtrlComponent();
		CtrlComponent(const CtrlComponent& other) = delete;
		CtrlComponent(CtrlComponent&& other) = delete;
		CtrlComponent& operator=(const CtrlComponent& other) = delete;
		CtrlComponent& operator=(CtrlComponent&& other) = delete;

		virtual void Update(const float deltaTime) = 0;

		GameObject* GetGameObject();
		bool Lock(std::chrono::duration<float> duration);
		void Unlock();
		void CtrlLoop();
	protected:
		std::thread mThread;
		std::atomic<bool> mRunThread;
		std::timed_mutex mMutex;
		Minigin* mpEngine;
		GameObject* mpGameObject;
	};
}
