#include "GameLoopHook.h"
#include "DiscordPresence.h"
#include "SAMP/samp.hpp"
#include "Config.h"

GameLoopHook::GameLoopHook() {
	gameloopHook_.install( std::make_tuple( this, &GameLoopHook::GameLoopHooked ) );
}

GameLoopHook::~GameLoopHook() {
	gameloopHook_.remove();
}

void GameLoopHook::GameLoopHooked( GameLoopPrototype fpHkOriginal ) {
	static bool isInitialized{ false };
	if ( !isInitialized ) {
		if ( SAMP::Base::isSAMPInitilize() ) {
			Config::Load();
			discordPresence_ = std::make_unique<DiscordPresence>();
			isInitialized = true; 
		}
	} else {
		if ( GetTickCount64() - UpdateRate > Config::Get()->UpdateRate ) {
			discordPresence_->Update();
			UpdateRate = GetTickCount64();
		}
	}
	return fpHkOriginal();
}