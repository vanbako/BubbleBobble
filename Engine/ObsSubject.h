#pragma once

namespace ieg
{
	class Observer;

	class ObsSubject
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
