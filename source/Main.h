#ifndef _MAIN_H_
#define _MAIN_H_

#include <memory>
#include <lemon/detour.hpp>

class AsiPlugin
{
	static constexpr const char* PluginFullName = "!DiscordPresence.asi";
	
	std::unique_ptr<class GameLoopHook> GameLoopHook_;
	std::unique_ptr<class RakHook> RakHook_;

	ULONGLONG UpdateRate = GetTickCount64();
public:
	explicit AsiPlugin();
	virtual ~AsiPlugin();
} AsiPlugin; // class AsiPlugin

#endif // !_MAIN_H_