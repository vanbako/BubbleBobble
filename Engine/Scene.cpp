module Engine:Scene;

import :Input;

using namespace ieg;

Scene::Scene(const std::string& name)
	: mName{ name }
	, mpInputManager(new InputManager{})
	, mpObjects{}
	, mIsFrozen{ false }
	, mFreezeTimer{ 0.f }
{
}

Scene::~Scene()
{
	for (auto pObject : mpObjects)
		delete pObject.second;
	delete mpInputManager;
}

void Scene::RemoveObject(SceneObject* pSceneObject)
{
	auto it{ mpObjects.begin() };
	while ((it != mpObjects.end()) && ((*it).second != pSceneObject))
		++it;
	if (it != mpObjects.end())
	{
		delete (*it).second;
		mpObjects.erase(it);
	}
}

void Scene::Update(const float deltaTime)
{
	if (mIsFrozen)
	{
		mFreezeTimer -= deltaTime;
		if (mFreezeTimer <= 0.f)
			mIsFrozen = false;
		return;
	}
	for (auto& objectPair : mpObjects)
		objectPair.second->CtrlLock();
	for (auto& objectPair : mpObjects)
		objectPair.second->ModelUpdate(deltaTime);
	for (auto& objectPair : mpObjects)
		objectPair.second->ModelCollision();
	for (auto& objectPair : mpObjects)
		if (objectPair.second->IsToBeDeleted())
		{
			delete objectPair.second;
			objectPair.second = nullptr;
		}
	auto it{ mpObjects.begin() };
	while (it != mpObjects.end())
	{
		auto itErase{ it };
		++it;
		if ((*itErase).second == nullptr)
			mpObjects.erase(itErase);
	}
	//mpObjects.erase(
	//	std::remove_if(mpObjects.begin(), mpObjects.end(),
	//		[](SceneObject* sceneObject) { return sceneObject == nullptr; }
	//	),
	//	mpObjects.end()
	//);
	for (auto& objectPair : mpObjects)
		objectPair.second->ModelSwitch();
	for (auto& objectPair : mpObjects)
		objectPair.second->ViewUpdate(deltaTime);
	for (auto& objectPair : mpObjects)
		objectPair.second->CtrlUnlock();
}

void Scene::Render() const
{
	for (auto& objectPair : mpObjects)
		objectPair.second->ViewRender();
}

void Scene::OnActivation(int value)
{
	for (auto& objectPair : mpObjects)
		objectPair.second->OnSceneActivation(value);
}

void Scene::OnDeactivation(int value)
{
	for (auto& objectPair : mpObjects)
		objectPair.second->OnSceneDeactivation(value);
}

void Scene::Freeze(const float delay)
{
	mFreezeTimer = delay;
	mIsFrozen = true;
}

InputManager* Scene::GetInputManager()
{
	return mpInputManager;
}
