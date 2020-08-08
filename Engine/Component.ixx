module;

#include <cstdarg>

export module Engine:Component;

import :Vector;
import std.core;

struct SDL_Texture;

namespace ieg
{
	class Minigin;
	class GameObject;
	class Minigin;
	class TransformModelComponent;
	class Texture2D;

	export class CtrlComponent
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

	export class ModelComponent
	{
	public:
		explicit ModelComponent(GameObject* pGameObject, Minigin* pEngine);
		virtual ~ModelComponent() = default;
		ModelComponent(const ModelComponent& other) = delete;
		ModelComponent(ModelComponent&& other) = delete;
		ModelComponent& operator=(const ModelComponent& other) = delete;
		ModelComponent& operator=(ModelComponent&& other) = delete;

		virtual void OnSceneActivation(int value) = 0;
		virtual void OnSceneDeactivation(int value) = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void Collision() = 0;
		virtual void Switch() = 0;

		GameObject* GetGameObject();
	protected:
		Minigin* mpEngine;
		GameObject* mpGameObject;
	};

	export class ColliderModelComponent final
		: public ModelComponent
	{
	public:
		explicit ColliderModelComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~ColliderModelComponent() = default;
		ColliderModelComponent(const ColliderModelComponent&) = delete;
		ColliderModelComponent(ColliderModelComponent&&) = delete;
		ColliderModelComponent& operator=(const ColliderModelComponent&) = delete;
		ColliderModelComponent& operator=(ColliderModelComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override { (deltaTime); };
		void Collision() override {};
		void Switch() override {};

		bool DoesCollide(TransformModelComponent* pTransformSelf, TransformModelComponent* pTransformOther, ColliderModelComponent* pColliderOther);
		const Vec2<int>& GetRelPos();
		const Vec2<int>& GetSize();
	private:
		Vec2<int> mRelPos;
		Vec2<int> mSize;
		bool DoesCollideOneWay(Vec2<int> posOne, Vec2<int> sizeOne, Vec2<int> posTwo, Vec2<int> sizeTwo);
		bool IsClamped(int mid, int one, int two);
	};

	export class TransformModelComponent final
		: public ModelComponent
	{
	public:
		explicit TransformModelComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~TransformModelComponent() = default;
		TransformModelComponent(const TransformModelComponent&) = delete;
		TransformModelComponent(TransformModelComponent&&) = delete;
		TransformModelComponent& operator=(const TransformModelComponent&) = delete;
		TransformModelComponent& operator=(TransformModelComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override;

		const Vec2<int>& GetPos() const;
		const bool GetIsLookingLeft() const;
		void SetPos(const int x, const int y);
		void SetPos(const Vec2<int> pos);
		void Move(const int deltaX, const int deltaY);
		void Move(const Vec2<int> delta);
		void SetIsLookingLeft(bool isLookingLeft);

		const Vec2<int>& GetNewPos() const;
		void ResetNewPos();
		void ResetNewPosX();
		void ResetNewPosY();
	private:
		Vec2<int>
			mCurPos,
			mNewPos;
		bool
			mCurIsLookingLeft,
			mNewIsLookingLeft;
	};

	export class ViewComponent
	{
	public:
		explicit ViewComponent(Minigin* pEngine);
		virtual ~ViewComponent() = default;
		ViewComponent(const ViewComponent& other) = delete;
		ViewComponent(ViewComponent&& other) = delete;
		ViewComponent& operator=(const ViewComponent& other) = delete;
		ViewComponent& operator=(ViewComponent&& other) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;
	protected:
		Minigin* mpEngine;
	};

	export class RenderViewComponent final
		: public ViewComponent
	{
	public:
		explicit RenderViewComponent(Minigin* pEngine);
		~RenderViewComponent() = default;
		RenderViewComponent(const RenderViewComponent&) = delete;
		RenderViewComponent(RenderViewComponent&&) = delete;
		RenderViewComponent& operator=(const RenderViewComponent&) = delete;
		RenderViewComponent& operator=(RenderViewComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Render() const override;

		void SetTransformComponent(TransformModelComponent* pTransformComponent);
		void SetTexture(const std::string& file);
		void SetTexture(Texture2D* pTexture);
		Texture2D* GetTexture();
		void SetSize(int width, int height);
		void SetIndex(int index);
		void SetType(int type);
		void SetAnimation(float delay, int startIndex, int stopIndex);
		Texture2D* SetTexture(SDL_Texture* pSDLTexture);
		Texture2D* ReplaceTexture(SDL_Texture* pSDLTexture);
		void SetIsSprite(bool isSprite);
		void SetIsOnOff(bool isOnOff, float onOffDelay = 0.15f);
	private:
		TransformModelComponent* mpTransformComponent;
		Texture2D* mpTexture;
		Vec2<int> mSize;
		int mIndex;
		int mType;
		float
			mDelay, mCurrDelay,
			mOnOffDelay, mCurrOnOffDelay;
		int
			mStartIndex,
			mStopIndex;
		bool mIsAnimating;
		bool mIsOnOff, mIsOn;
		bool mIsSprite;
	};
}
