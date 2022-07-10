#ifndef _GAME_LOOP_HOOK_
#define _GAME_LOOP_HOOK_

#include <lemon/detour.hpp>

using GameLoopPrototype = void( __cdecl* )();

class GameLoopHook
{
	lemon::detour<GameLoopPrototype> gameloopHook_{ 0x748DA3 };

	ULONGLONG UpdateRate = GetTickCount64();
public:
	GameLoopHook();
	~GameLoopHook();
protected:
	void GameLoopHooked( GameLoopPrototype fpHkOriginal );
}; // class GameLoopHook

#endif // !_GAME_LOOP_HOOK_