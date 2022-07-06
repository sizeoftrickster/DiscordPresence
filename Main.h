#ifndef _MAIN_H_
#define _MAIN_H_

#include <memory>

class AsiPlugin
{
	static constexpr const char* PluginFullName = "!DiscordPresence.asi";

	std::unique_ptr<class GameLoopHook> GameLoopHook_;
public:
	explicit AsiPlugin();
	virtual ~AsiPlugin();
} AsiPlugin; // class AsiPlugin

#endif // !_MAIN_H_