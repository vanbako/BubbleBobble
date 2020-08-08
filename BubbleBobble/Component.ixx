export module BubbleBobble:Component;

import Engine;

namespace ieg
{
	class JumpCommand;
	class LeftCommand;
	class RightCommand;
	class HudObserver;
	class StandingState;
	class JumpingState;
	class FallingState;
	class FloatingState;
	class CharacterKineticState;
	class ReadyState;
	class FiringState;
	class ReloadingState;
	class CharacterWeaponState;
	class LivingState;
	class DyingState;
	class InvincibleState;
	class AvatarHealthState;
	class BubbleCaptureState;
	class BubbleFloatingState;
	class BubblePoppingState;
	class BubbleKineticState;
	class ObjectsManager;
	class BufferManager;
	enum class AvatarType;

	class BubbleCtrlComponent final
		: public CtrlComponent
	{
	public:
		explicit BubbleCtrlComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~BubbleCtrlComponent() = default;
		BubbleCtrlComponent(const BubbleCtrlComponent&) = delete;
		BubbleCtrlComponent(BubbleCtrlComponent&&) = delete;
		BubbleCtrlComponent& operator=(const BubbleCtrlComponent&) = delete;
		BubbleCtrlComponent& operator=(BubbleCtrlComponent&&) = delete;

		void Update(const float deltaTime) override;
	};

	export enum class NpcMove
	{
		Idle,
		Left,
		Right,
		Count
	};

	export class NpcCtrlComponent final
		: public CtrlComponent
	{
	public:
		explicit NpcCtrlComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~NpcCtrlComponent();
		NpcCtrlComponent(const NpcCtrlComponent&) = delete;
		NpcCtrlComponent(NpcCtrlComponent&&) = delete;
		NpcCtrlComponent& operator=(const NpcCtrlComponent&) = delete;
		NpcCtrlComponent& operator=(NpcCtrlComponent&&) = delete;

		void Update(const float deltaTime) override;
		void SetMove(NpcMove move);
		void SwitchX();
	private:
		float mTimer;
		NpcMove mMove;
		JumpCommand* mpJumpCommand;
		LeftCommand* mpLeftCommand;
		RightCommand* mpRightCommand;

		static const int mMinDelay;
		static const int mMaxDelay;
	};

	export class CharacterComponent
		: public ModelComponent
	{
	public:
		explicit CharacterComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		virtual ~CharacterComponent();
		CharacterComponent(const CharacterComponent&) = delete;
		CharacterComponent(CharacterComponent&&) = delete;
		CharacterComponent& operator=(const CharacterComponent&) = delete;
		CharacterComponent& operator=(CharacterComponent&&) = delete;

		virtual void Update(const float deltaTime);
		virtual void Collision();
		virtual void Switch();

		virtual void Fire();
		virtual void Jump();
		virtual void Left();
		virtual void Right();

		virtual void SetFloatingState();
		bool IsFloatingState();
		virtual void SetFallingState();
		virtual void SetJumpingState();
		virtual void SetStandingState();
		virtual void SetReadyState();
		virtual void SetFiringState();
		virtual void SetReloadingState();
		virtual bool HasBubbleCollision();

		ObsSubject* GetObsSubject() { return mpObsSubject; };
		void SetLevel(GameObject* pLevel) { mpGOLevel = pLevel; };
		bool HasWallCollision();

		static float GetMoveVer2PixelsTime() { return mMoveVer2PixelsTime; };
	protected:
		GameObject* mpGOLevel;
		ObsSubject* mpObsSubject;
		StandingState* mpStandingState;
		JumpingState* mpJumpingState;
		FallingState* mpFallingState;
		FloatingState* mpFloatingState;
		CharacterKineticState
			* mpCurKineticState,
			* mpNewKineticState;
		ReadyState* mpReadyState;
		FiringState* mpFiringState;
		ReloadingState* mpReloadingState;
		CharacterWeaponState
			* mpCurWeaponState,
			* mpNewWeaponState;
		int mIsHorMoving;
		float mMoveHorDelay;
		bool mHasWallCollision;

		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};

	export enum class AvatarEvent
	{
		Score,
		Die
	};

	export class AvatarComponent final
		: public CharacterComponent
	{
	public:
		explicit AvatarComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~AvatarComponent();
		AvatarComponent(const AvatarComponent&) = delete;
		AvatarComponent(AvatarComponent&&) = delete;
		AvatarComponent& operator=(const AvatarComponent&) = delete;
		AvatarComponent& operator=(AvatarComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override;

		void SetAvatarType(AvatarType avatarType);
		AvatarType GetAvatarType();
		ObsSubject* GetObsSubject();

		void SetJumpingState() override;
		void SetFiringState() override;
		void SetLivingState();
		void SetDyingState();
		void SetInvincibleState();

		void SetRenderInvincible(bool setOn);

		void FireBubble();
		void Spawn();

		void Fire() override;
		void Jump() override;
		void Left() override;
		void Right() override;
	private:
		ObjectsManager* mpObjectsManager;
		AvatarType mAvatarType;
		LivingState* mpLivingState;
		DyingState* mpDyingState;
		InvincibleState* mpInvincibleState;
		AvatarHealthState
			* mpCurHealthState,
			* mpNewHealthState;
		ObsSubject* mpObsSubject;
		int mJumpSoundId, mCatchSoundId;
	};

	export enum class NpcType
	{
		ZenChan = 0,
		Hidegons,
		Banebou,
		PulPul,
		Monsta,
		Drunk,
		Maita,
		Invader,
		Count
	};

	export enum class NpcEvent
	{
		Die
	};

	export class NpcComponent final
		: public CharacterComponent
	{
	public:
		explicit NpcComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~NpcComponent() = default;
		NpcComponent(const NpcComponent&) = delete;
		NpcComponent(NpcComponent&&) = delete;
		NpcComponent& operator=(const NpcComponent&) = delete;
		NpcComponent& operator=(NpcComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override;

		void SetNpcType(NpcType npcType);
		NpcType GetNpcType();

		void Jump() override;
		void Left() override;
		void Right() override;
		void Pop();
		void Release();
		bool Capture();
	private:
		NpcType mNpcType;
	};

	export class IntroComponent final
		: public ModelComponent
	{
	public:
		explicit IntroComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~IntroComponent();
		IntroComponent(const IntroComponent&) = delete;
		IntroComponent(IntroComponent&&) = delete;
		IntroComponent& operator=(const IntroComponent&) = delete;
		IntroComponent& operator=(IntroComponent&&) = delete;

		void OnSceneActivation(int value) override;
		void OnSceneDeactivation(int value) override;
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		void SetStartScene(Scene* pScene);

		void Start(int players) const;
	private:
		Scene* mpStartScene;
		Audio* mpAudio;
		int mStartSoundId;
		int mIntroSoundId;
		float mStartWait;
		bool mStartAudio;
	};

	export class BubbleComponent final
		: public ModelComponent
	{
	public:
		explicit BubbleComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~BubbleComponent();
		BubbleComponent(const BubbleComponent&) = delete;
		BubbleComponent(BubbleComponent&&) = delete;
		BubbleComponent& operator=(const BubbleComponent&) = delete;
		BubbleComponent& operator=(BubbleComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override;

		void SetLevel(GameObject* pLevel);
		void SetIsFiringLeft(bool isFiringLeft);
		bool IsFiringLeft();

		virtual void SetCaptureState();
		virtual void SetFloatingState();
		bool IsFloatingState();
		virtual void SetPoppingState();
	private:
		GameObject* mpGOLevel;
		bool mIsFiringLeft;
		BubbleCaptureState* mpCaptureState;
		BubbleFloatingState* mpFloatingState;
		BubblePoppingState* mpPoppingState;
		BubbleKineticState
			* mpCurKineticState,
			* mpNewKineticState;
	};

	enum class CandyType;

	export class CandyComponent final
		: public ModelComponent
	{
	public:
		explicit CandyComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~CandyComponent() = default;
		CandyComponent(const CandyComponent&) = delete;
		CandyComponent(CandyComponent&&) = delete;
		CandyComponent& operator=(const CandyComponent&) = delete;
		CandyComponent& operator=(CandyComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override {};

		void SetLevel(GameObject* pLevel);
		void Seize();
		void SetCandyType(CandyType candyType);
	private:
		GameObject* mpGOLevel;
	};

	export class HudComponent final
		: public ModelComponent
	{
	public:
		explicit HudComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~HudComponent();
		HudComponent(const HudComponent&) = delete;
		HudComponent(HudComponent&&) = delete;
		HudComponent& operator=(const HudComponent&) = delete;
		HudComponent& operator=(HudComponent&&) = delete;

		void OnSceneActivation(int value) override;
		void OnSceneDeactivation(int value) override;
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		HudObserver* GetObserver();
		GameObject* GetLevel();
		void NextLevel();

		void DeltaScore(int value);
		void AvatarDie(int avatar);
		void GameOver();
		void BackToIntro();
	private:
		int mPlayers;
		Audio* mpAudio;
		BufferManager* mpBufferManager;
		ColorRGBA8* mpPalette;
		Scene* mpIntroScene;
		int mLevel;
		int mGameSoundId, mGameOverSoundId;
		ObjectsManager* mpObjectsManager;
		GameObject
			* mpGOLevel,
			* mpGOLevelNumber;
		HudObserver* mpHudObserver;
		bool mIsGameOver;
		std::vector<int> mScores;
		std::vector<int> mLives;
		std::vector<GameObject*> mpGOScores;
		std::vector<GameObject*> mpGOLives;
		bool mEndLevel;

		static const int mColorIndex[];
		static const int mStartLives;
		static const int mMaxLives;
		static const float mGameOverDelay;

		void CreateLevelNumber();
		void CreateScores();
		void CreateLives();
		void DrawLives();
		void DrawScores();
		void LivesInit();
		void ScoresInit();
	};

	enum class LevelEvent
	{
		End
	};

	export class LevelComponent final
		: public ModelComponent
	{
	public:
		explicit LevelComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~LevelComponent();
		LevelComponent(const LevelComponent&) = delete;
		LevelComponent(LevelComponent&&) = delete;
		LevelComponent& operator=(const LevelComponent&) = delete;
		LevelComponent& operator=(LevelComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		ObsSubject* GetObsSubject();
		unsigned short CheckAvatarCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		unsigned short CheckRectangleCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		unsigned short CheckRectanglePosCollision(const Vec2<int>& pos, ColliderModelComponent* pCollider);
		GameObject* CheckNpcCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		GameObject* CheckCandyCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		bool CheckBubbleNpcCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		bool CheckBubbleCollision(TransformModelComponent* pTransform, ColliderModelComponent* pCollider);
		bool CheckCollisionPos(int x, int y);
		void SpawnAvatar(AvatarType avatarType);
		void SpawnCandy(NpcType npcType, TransformModelComponent* pTransform);
		void CheckLastNpc();
	private:
		int mLevel;
		int mPlayers;
		float mEndLevelTime;
		float mTest;
		ObjectsManager* mpObjectsManager;
		char
			* mpLayout,
			* mpEnemyData;
		ColorRGBA8* mpPalette;
		ObsSubject* mpObsSubject;
		bool mEndLevel;

		static const float mEndLevelWait;
	};

	export class StartComponent final
		: public ModelComponent
	{
	public:
		explicit StartComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~StartComponent();
		StartComponent(const StartComponent&) = delete;
		StartComponent(StartComponent&&) = delete;
		StartComponent& operator=(const StartComponent&) = delete;
		StartComponent& operator=(StartComponent&&) = delete;

		void OnSceneActivation(int value) override;
		void OnSceneDeactivation(int value) override;
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		void SetStartScene(Scene* pScene);
	private:
		int mPlayers;
		Scene* mpStartScene;
		Audio* mpAudio;
		int mStartSoundId;
		float mStartWait;
		float mSwapWait;

		static const float mStartWaitVal;
	};

	export class TextComponent final
		: public ModelComponent
	{
	public:
		explicit TextComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~TextComponent() = default;
		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void OnSceneDeactivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		void SetText(const std::string& text, int colorIndex);
		void SetRenderViewComponent(RenderViewComponent* pRenderViewComponent);
	private:
		BufferManager* mpBufferManager;
		ColorRGBA8* mpPalette;
		std::string mText;
		int mColorIndex;
		bool mNeedsUpdate;
		RenderViewComponent* mpRenderViewComponent;

		static const int mWidth;
		static const int mHeight;
		static const int mChrWidth;
		static const int mChrHeight;

		void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc);
		void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str);
	};
}
