#pragma once
#include "../Engine/Component.h"

namespace ieg
{
	class Audio;

	class ActorComponent final
		: public Component
	{
	public:
		explicit ActorComponent() = default;
		~ActorComponent() = default;

		virtual void Update(const float deltaTime) override { (deltaTime); };
		virtual void Render() const override {};

		void Left() const {};
		void Right() const {};
		void Fire() const {};
		void Jump() const {};
	};
}
