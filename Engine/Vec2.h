#pragma once

namespace ieg
{
	template<class T>
	class Vec2 final
	{
	public:
		explicit Vec2()
			: Vec2(T{}, T{})
		{};
		explicit Vec2(T x, T y)
			: mX{ x }
			, mY{ y }
		{};
		~Vec2() = default;
		Vec2(const Vec2& other) = default;
		Vec2(Vec2&& other) = default;
		Vec2& operator=(const Vec2& other) = default;
		Vec2& operator=(Vec2&& other) = default;

		Vec2<T> operator+(const Vec2<T>& rhs) const
		{
			return Vec2<T> { mX + rhs.mX, mY + rhs.mY };
		};

		const T& GetX() const { return mX; };
		const T& GetY() const { return mY; };
		void SetX(T x) { mX = x; };
		void SetY(T y) { mY = y; };
		void SetXY(T x, T y) { mX = x; mY = y; };
		void Move(T x, T y) { mX += x; mY += y; };
	private:
		T mX;
		T mY;
	};
}