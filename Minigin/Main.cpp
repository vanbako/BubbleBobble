#include "MiniginPCH.h"

#if _DEBUG
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

int main(int, char* [])
{
	ieg::Minigin engine;
	engine.Run();
	return 0;
}
