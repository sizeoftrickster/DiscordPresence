#include "Main.h"
#include "Utility.h"
#include "GameLoopHook.h"
#include "RakHook.h"

AsiPlugin::AsiPlugin() {
	if ( GetModuleHandleA( PluginFullName ) != Utility::GetCurrentModule() )
		return;
	GameLoopHook_ = std::make_unique<GameLoopHook>();
	RakHook_ = std::make_unique<RakHook>();
}

AsiPlugin::~AsiPlugin() {

}