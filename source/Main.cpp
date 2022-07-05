#include "Main.h"
#include "Utility.h"
#include "GameLoopHook.h"

AsiPlugin::AsiPlugin() {
	if ( GetModuleHandleA( PluginFullName ) != Utility::GetCurrentModule() )
		return;
	GameLoopHook_ = std::make_unique<GameLoopHook>();
}

AsiPlugin::~AsiPlugin() {

}