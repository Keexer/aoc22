#pragma once

#include <iostream>

namespace details
{

	template <typename T>
	class Delegator
	{
	public:
		typedef void (T::* Fn)();

		Delegator(T&& t, Fn fn)
			: mT(std::forward<T>(t))
			, mFn(fn)
		{}

		void operator()()
		{
			(mT.*mFn)();
		}

	private:
		T mT;
		Fn mFn;
	};

	class TypeErasedDelegator
	{
	public:
		template <typename T>
		TypeErasedDelegator(T&& t)
			: mT(std::make_shared<Concrete<T> >(std::forward<T>(t)))
		{}

		void solve()
		{
			mT->solve();
		}

		class Concept
		{
		public:
			virtual void solve() = 0;
		};

		template <typename T>
		class Concrete : public Concept
		{
		public:
			Concrete(T&& t)
				: mT(std::forward<T>(t))
			{}

			virtual void solve() final
			{
				mT();
			}

		private:
			T mT;
		};

	private:
		std::shared_ptr<Concept> mT;
	};

}

class DefaultDay
{
public:
	void solve()
	{
		std::cout << "Day is not yet solved\n";
	}
};

class DaysHandler
{
public:
	DaysHandler()
	{
		mDays.assign(25, details::TypeErasedDelegator{ details::Delegator{ DefaultDay{}, &DefaultDay::solve } });
	}

	size_t numberOfDays() const
	{
		return mDays.size();
	}

	template <typename T>
	void addDay(T day, size_t index)
	{
		details::TypeErasedDelegator t{ details::Delegator{T{}, &T::solve} };
		mDays[index - 1] = t;
	}

	void solveDay(size_t day)
	{
		const size_t index = day - 1;
		if (index < numberOfDays())
		{
			mDays[index].solve();
		}
		else
		{
			std::cout << "Day does not exist\n";
		}
	}

private:
	std::vector<details::TypeErasedDelegator> mDays;
};
