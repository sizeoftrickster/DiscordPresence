#include "Main.h"
#include "Utility.h"
#include "GameLoopHook.h"
#include "RakHook.h"
#include "Config.h"

AsiPlugin::AsiPlugin() {
	Config::Load();
	if ( GetModuleHandleA( PluginFullName ) != Utility::GetCurrentModule() || !Config::Get()->EnablePresence )
		return;
	GameLoopHook_ = std::make_unique<GameLoopHook>();
	RakHook_ = std::make_unique<RakHook>();
}

AsiPlugin::~AsiPlugin() {

}