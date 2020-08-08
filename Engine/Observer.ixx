export module Engine:Observer;

import std.core;

namespace ieg
{
	export class Observer
	{
	public:
		explicit Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(Observer&&) = delete;

		virtual void OnNotify(size_t subject, int event, int value) = 0;
	};

	export class ObsSubject
	{
	public:
		explicit ObsSubject() = default;
		virtual ~ObsSubject() = default;
		ObsSubject(const ObsSubject&) = delete;
		ObsSubject(ObsSubject&&) = delete;
		ObsSubject& operator=(const ObsSubject&) = delete;
		ObsSubject& operator=(ObsSubject&&) = delete;

		void Notify(size_t subject, int event, int value);
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
	private:
		std::vector<Observer*> mpObservers;
	};
}
