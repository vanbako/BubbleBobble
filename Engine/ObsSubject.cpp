module Engine:Observer;

using namespace ieg;

void ObsSubject::Notify(size_t subject, int event, int value)
{
	for (auto pObserver : mpObservers)
		pObserver->OnNotify(subject, event, value);
}

void ObsSubject::AddObserver(Observer* pObserver)
{
	mpObservers.push_back(pObserver);
}

void ObsSubject::RemoveObserver(Observer* pObserver)
{
	mpObservers.erase(
		std::remove_if(mpObservers.begin(), mpObservers.end(),
			[pObserver](Observer* pObs) { return pObs == pObserver; }
		),
		mpObservers.end()
	);
}
