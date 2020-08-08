export module BubbleBobble:State;

import Engine;

namespace ieg
{
	export class CharacterWeaponState
		: public State
	{
	public:
		explicit CharacterWeaponState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		virtual ~CharacterWeaponState() = default;
		CharacterWeaponState(const CharacterWeaponState&) = delete;
		CharacterWeaponState(CharacterWeaponState&&) = delete;
		CharacterWeaponState& operator=(const CharacterWeaponState&) = delete;
		CharacterWeaponState& operator=(CharacterWeaponState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Fire() = 0;
		virtual void FiringDone() = 0;
		virtual void ReloadDone() = 0;
	};

	export class FiringState final
		: public CharacterWeaponState
	{
	public:
		explicit FiringState(ModelComponent* pModelComponent);
		~FiringState() = default;
		FiringState(const FiringState&) = delete;
		FiringState(FiringState&&) = delete;
		FiringState& operator=(const FiringState&) = delete;
		FiringState& operator=(FiringState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Fire() override {};
		virtual void FiringDone() override;
		virtual void ReloadDone() override {};
	private:
		float mFiringTimer;

		static const float mFiringTime;
	};

	export class ReadyState final
		: public CharacterWeaponState
	{
	public:
		explicit ReadyState(ModelComponent* pModelComponent)
			: CharacterWeaponState(pModelComponent)
		{};
		~ReadyState() = default;
		ReadyState(const ReadyState&) = delete;
		ReadyState(ReadyState&&) = delete;
		ReadyState& operator=(const ReadyState&) = delete;
		ReadyState& operator=(ReadyState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Fire() override;
		virtual void FiringDone() override {};
		virtual void ReloadDone() override {};
	};

	export class ReloadingState final
		: public CharacterWeaponState
	{
	public:
		explicit ReloadingState(ModelComponent* pModelComponent);
		~ReloadingState() = default;
		ReloadingState(const ReloadingState&) = delete;
		ReloadingState(ReloadingState&&) = delete;
		ReloadingState& operator=(const ReloadingState&) = delete;
		ReloadingState& operator=(ReloadingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Fire() override {};
		virtual void FiringDone() override {};
		virtual void ReloadDone() override;
	private:
		float mReloadTimer;

		static const float mReloadTime;
	};

	export class CharacterKineticState
		: public State
	{
	public:
		explicit CharacterKineticState(ModelComponent* pModelComponent);
		virtual ~CharacterKineticState() = default;
		CharacterKineticState(const CharacterKineticState&) = delete;
		CharacterKineticState(CharacterKineticState&&) = delete;
		CharacterKineticState& operator=(const CharacterKineticState&) = delete;
		CharacterKineticState& operator=(CharacterKineticState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Jump() = 0;
		virtual void Fall() = 0;
		virtual void Land() = 0;
		virtual void Capture() = 0;
	};

	export class StandingState final
		: public CharacterKineticState
	{
	public:
		explicit StandingState(ModelComponent* pModelComponent)
			: CharacterKineticState(pModelComponent)
		{};
		~StandingState() = default;
		StandingState(const StandingState&) = delete;
		StandingState(StandingState&&) = delete;
		StandingState& operator=(const StandingState&) = delete;
		StandingState& operator=(StandingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Jump() override;
		virtual void Fall() override;
		virtual void Land() override {};
		virtual void Capture() override;
	};

	export class JumpingState final
		: public CharacterKineticState
	{
	public:
		explicit JumpingState(ModelComponent* pModelComponent);
		~JumpingState() = default;
		JumpingState(const JumpingState&) = delete;
		JumpingState(JumpingState&&) = delete;
		JumpingState& operator=(const JumpingState&) = delete;
		JumpingState& operator=(JumpingState&&) = delete;

		void ResetJumpHeight();
		virtual void Update(const float deltaTime) override;
		virtual void Jump() override {};
		virtual void Fall() override;
		virtual void Land() override {};
		virtual void Capture() override;
	private:
		int	mIsVerMoving;
		int mJumpHeight;
		float mMoveVerDelay;

		static const int mMaxJumpHeight;
	};

	export class FloatingState final
		: public CharacterKineticState
	{
	public:
		explicit FloatingState(ModelComponent* pModelComponent);
		~FloatingState() = default;
		FloatingState(const FloatingState&) = delete;
		FloatingState(FloatingState&&) = delete;
		FloatingState& operator=(const FloatingState&) = delete;
		FloatingState& operator=(FloatingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Jump() override {};
		virtual void Fall() override;
		virtual void Land() override {};
		virtual void Capture() override {};

		void ResetTimer();
	private:
		float mFloatingTimer;
		float
			mMoveHorDelay,
			mMoveVerDelay;

		static const float mFloatingTime;
		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};

	export class FallingState final
		: public CharacterKineticState
	{
	public:
		explicit FallingState(ModelComponent* pModelComponent);
		~FallingState() = default;
		FallingState(const FallingState&) = delete;
		FallingState(FallingState&&) = delete;
		FallingState& operator=(const FallingState&) = delete;
		FallingState& operator=(FallingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Jump() override;
		virtual void Fall() override {};
		virtual void Land() override;
		virtual void Capture() override;
	private:
		int	mIsVerMoving;
		float mMoveVerDelay;
	};

	export class BubbleKineticState
		: public State
	{
	public:
		explicit BubbleKineticState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		virtual ~BubbleKineticState() = default;
		BubbleKineticState(const BubbleKineticState&) = delete;
		BubbleKineticState(BubbleKineticState&&) = delete;
		BubbleKineticState& operator=(const BubbleKineticState&) = delete;
		BubbleKineticState& operator=(BubbleKineticState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void CaptureDone() = 0;
		virtual void Pop() = 0;
		virtual void PopDone() = 0;
	};

	export class BubbleCaptureState final
		: public BubbleKineticState
	{
	public:
		explicit BubbleCaptureState(ModelComponent* pModelComponent);
		~BubbleCaptureState() = default;
		BubbleCaptureState(const BubbleCaptureState&) = delete;
		BubbleCaptureState(BubbleCaptureState&&) = delete;
		BubbleCaptureState& operator=(const BubbleCaptureState&) = delete;
		BubbleCaptureState& operator=(BubbleCaptureState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void CaptureDone() override;
		virtual void Pop() override {};
		virtual void PopDone() override {};
	private:
		float mCaptureTimer;
		float mMoveHorDelay;

		static const float mCaptureTime;
		static const float mMoveHor2PixelsTime;
	};

	export class BubbleFloatingState final
		: public BubbleKineticState
	{
	public:
		explicit BubbleFloatingState(ModelComponent* pModelComponent);
		~BubbleFloatingState() = default;
		BubbleFloatingState(const BubbleFloatingState&) = delete;
		BubbleFloatingState(BubbleFloatingState&&) = delete;
		BubbleFloatingState& operator=(const BubbleFloatingState&) = delete;
		BubbleFloatingState& operator=(BubbleFloatingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void CaptureDone() override {};
		virtual void Pop() override;
		virtual void PopDone() override {};
	private:
		float mFloatingTimer;
		float
			mMoveHorDelay,
			mMoveVerDelay;

		static const float mFloatingTime;
		static const float mMoveHor2PixelsTime;
		static const float mMoveVer2PixelsTime;
	};

	export class BubblePoppingState final
		: public BubbleKineticState
	{
	public:
		explicit BubblePoppingState(ModelComponent* pModelComponent);
		~BubblePoppingState() = default;
		BubblePoppingState(const BubblePoppingState&) = delete;
		BubblePoppingState(BubblePoppingState&&) = delete;
		BubblePoppingState& operator=(const BubblePoppingState&) = delete;
		BubblePoppingState& operator=(BubblePoppingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void CaptureDone() override {};
		virtual void Pop() override {};
		virtual void PopDone() override;
	private:
		float mPoppingTimer;

		static const float mPoppingTime;
	};

	export class AvatarHealthState
		: public State
	{
	public:
		explicit AvatarHealthState(ModelComponent* pModelComponent)
			: State(pModelComponent)
		{};
		virtual ~AvatarHealthState() = default;
		AvatarHealthState(const AvatarHealthState&) = delete;
		AvatarHealthState(AvatarHealthState&&) = delete;
		AvatarHealthState& operator=(const AvatarHealthState&) = delete;
		AvatarHealthState& operator=(AvatarHealthState&&) = delete;

		virtual void Update(const float deltaTime) = 0;
		virtual void Die() = 0;
		virtual void Spawn() = 0;
		virtual void InvincibleDone() = 0;
	};

	export class DyingState final
		: public AvatarHealthState
	{
	public:
		explicit DyingState(ModelComponent* pModelComponent);
		~DyingState() = default;
		DyingState(const DyingState&) = delete;
		DyingState(DyingState&&) = delete;
		DyingState& operator=(const DyingState&) = delete;
		DyingState& operator=(DyingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Die() override {};
		virtual void Spawn() override;
		virtual void InvincibleDone() override {};
	private:
		float mDyingTimer;

		static const float mDyingTime;
	};

	export class InvincibleState final
		: public AvatarHealthState
	{
	public:
		explicit InvincibleState(ModelComponent* pModelComponent);
		~InvincibleState() = default;
		InvincibleState(const InvincibleState&) = delete;
		InvincibleState(InvincibleState&&) = delete;
		InvincibleState& operator=(const InvincibleState&) = delete;
		InvincibleState& operator=(InvincibleState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Die() override {};
		virtual void Spawn() override {};
		virtual void InvincibleDone() override;
	private:
		float mInvincibleTimer;

		static const float mInvincibleTime;
	};

	class LivingState final
		: public AvatarHealthState
	{
	public:
		explicit LivingState(ModelComponent* pModelComponent)
			: AvatarHealthState(pModelComponent)
		{};
		~LivingState() = default;
		LivingState(const LivingState&) = delete;
		LivingState(LivingState&&) = delete;
		LivingState& operator=(const LivingState&) = delete;
		LivingState& operator=(LivingState&&) = delete;

		virtual void Update(const float deltaTime) override;
		virtual void Die() override;
		virtual void Spawn() override {};
		virtual void InvincibleDone() override {};
	};
}
