export module BubbleBobble:Observer;

import Engine;

namespace ieg
{
	class HudComponent;

	class HudObserver
		: public Observer
	{
	public:
		HudObserver(HudComponent* pHudComponent);
		virtual void OnNotify(size_t subject, int event, int value) override;
	private:
		HudComponent* mpHudComponent;
	};
}
