#pragma once

#include <memory>
#include <vector>
#include <utility>

namespace details
{
class ErasedTypeDay
{
public:
	template <typename T>
	ErasedTypeDay(T&& t)
		: mObject(std::make_shared<Concrete<T> >(std::forward<T>(t)))
	{}

	void extract()
	{
		//mObject->extract();
	}

	void presentA()
	{
		mObject->presentA();
	}

	void presentB()
	{
		mObject->presentB();
	}

	class Concept
	{
	public:
		virtual ~Concept() {};
		virtual void extract() = 0;
		virtual void presentA() = 0;
		virtual void presentB() = 0;
	};

	template <typename T>
	class Concrete : public Concept
	{
	public:
		Concrete(T&& t)
			: mObject(std::forward<T>(t))
		{}

		void extract() override
		{
			//mObject.extract();
		}

		void presentA() override
		{
			//mObject.presentA();
		}

		void presentB() override
		{
			//mObject.presentB();
		}
			
	private:
		T mObject;
	};

private:
	std::shared_ptr<Concept> mObject;
};
}

class DaysHandler
{
public:
	DaysHandler()
	{}

	template <typename T>
	void addDay(T&& t)
	{
		mDays.push_back(details::ErasedTypeDay(T{}));
	}

private:
	std::vector<details::ErasedTypeDay> mDays {};
};