#include "DiscordPresence.h"
#include "Discord/discord_rpc.h"
#include "SAMP/samp.hpp"
#include "GTA/game.hpp"
#include "Utility.h"
#include "RakHook.h"
#include "Config.h"

DiscordPresence* DiscordPresence::self{ nullptr };

DiscordPresence::DiscordPresence() {
	DiscordEventHandlers eventHandler;
	memset( &eventHandler, 0, sizeof( eventHandler ) );
	Discord_Initialize( Config::Get()->ApplicationID.c_str(), &eventHandler, NULL, nullptr );
}

DiscordPresence::~DiscordPresence() {
	Discord_Shutdown();
}

DiscordPresence* DiscordPresence::CreateInstance() {
	if ( self )
		return self;
	self = new DiscordPresence();
	return self;
}

void DiscordPresence::DeleteInstance() {
	if ( self ) {
		delete self;
		self = nullptr;
	}
}

void DiscordPresence::Update() {
	DiscordRichPresence richPresence;
	memset( &richPresence, 0, sizeof( richPresence ) );

	int serverIndex = GetServerIndex( SAMP::Base::CreateInstance()->GetServer() );

	// Info //
	richPresence.state = GetPlayerState();
	richPresence.details = GetPlayerDetails();
	// ServerLogo //
	richPresence.largeImageKey = GetServerLogo( serverIndex );
	richPresence.largeImageText = GetServerInfo();
	// WeaponLogo //
	if ( Config::Get()->EnableShowingGuns ) {
		auto [weaponIndex, weaponName] = CPed::GetWeaponInfo();
		richPresence.smallImageKey = GetWeaponLogo( weaponIndex );
		richPresence.smallImageText = weaponName.c_str();
	}
	// FirstButton //
	if ( Config::Get()->EnableShowingFirstButton ) {
		richPresence.button1_label = Config::Get()->FirstButtonText.c_str();
		richPresence.button1_url = Config::Get()->FirstButtonURL.c_str();
	}
	// SecondButton //
	if ( Config::Get()->EnableShowingSecondButton ) {
		richPresence.button2_label = Config::Get()->SecondButtonText.c_str();
		richPresence.button2_url = Config::Get()->SecondButtonURL.c_str();
	}
	// Time //
	richPresence.startTimestamp = Timestamp;

	Discord_UpdatePresence( &richPresence );
}

int DiscordPresence::GetServerIndex( const char* serverIp ) {
	int resultIndex = -1;
	for ( size_t index = 0; index < ServersIP.size(); index++ ) {
		if ( serverIp == ServersIP[index] ) {
			resultIndex = index;
			break;
		}
	}
	return resultIndex;
}

const char* DiscordPresence::GetPlayerState() {
	if ( !Config::Get()->EnableShowingActions )
		return Config::Get()->DisabledActionsText.c_str();	
	const char* FinalAction = Config::Get()->DoesNothing.c_str();
	
	switch ( RakHook::GetPacketsAction() ) {
		case ( RakHook::PacketsActions::TRYING_CONNECTION ): {
			FinalAction = Config::Get()->TryingConnection.c_str();
			break;
		}
		case ( RakHook::PacketsActions::DOES_NOTHING ): {
			switch ( RakHook::GetRPCAction() ) {
				case ( RakHook::RPCActions::SHOW_DIALOG ): {
					FinalAction = Config::Get()->ShowDialog.c_str();
					break;
				}
				case ( RakHook::RPCActions::SHOW_TEXTDRAW ): {
					FinalAction = Config::Get()->ShowTextDraw.c_str();
					break;
				}
				case ( RakHook::RPCActions::SHOW_GAMETEXT ): {
					FinalAction = Config::Get()->ShowGameText.c_str();
					break;
				}
				case ( RakHook::RPCActions::DOES_NOTHING ): {	
					switch ( CPed::GetTransportState() ) {
						case ( CPed::TransportState::AUTOMOBILE ): {
							FinalAction = Config::Get()->Automobile.c_str();
							break;
						}
						case ( CPed::TransportState::MTRUCK ): {
							FinalAction = Config::Get()->MonsterTruck.c_str();
							break;
						}
						case ( CPed::TransportState::QUAD ): {
							FinalAction = Config::Get()->Quad.c_str();
							break;
						}
						case ( CPed::TransportState::HELICOPTER ): {
							FinalAction = Config::Get()->Helicopter.c_str();
							break;
						}
						case ( CPed::TransportState::PLANE ): {
							FinalAction = Config::Get()->Plane.c_str();
							break;
						}
						case ( CPed::TransportState::BOAT ): {
							FinalAction = Config::Get()->Boat.c_str();
							break;
						}
						case ( CPed::TransportState::TRAIN ): {
							FinalAction = Config::Get()->Train.c_str();
							break;
						}
						case ( CPed::TransportState::BIKE ): {
							FinalAction = Config::Get()->Bike.c_str();
							break;
						}
						case ( CPed::TransportState::BMX ): {
							FinalAction = Config::Get()->BMX.c_str();
							break;
						}
						case ( CPed::TransportState::UNKNOWN ): {
							switch ( CPed::GetPedRunningStatus() ) {
								case ( CPed::PedState::RUNNING ): {
									FinalAction = Config::Get()->Running.c_str();
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	return FinalAction;
}
const char* DiscordPresence::GetPlayerDetails() {
	char* buffer = new char[128];
	auto playerPool = SAMP::Base::CreateInstance()->Pools()->PlayerPool();
	sprintf( buffer, "%s[%d]", Utility::cp1251ToUTF8( playerPool->GetLocalPlayerNickname().data() ).data(), playerPool->GetLocalPlayerId() );
	return buffer;
}

const char* DiscordPresence::GetServerLogo( int serverIndex ) {
	if ( serverIndex >= 0 && serverIndex <= 21 )
		return Config::Get()->ArizonaRP.c_str();
	else if ( serverIndex >= 22 && serverIndex <= 25 )
		return Config::Get()->SAMPRP.c_str();
	else if ( serverIndex == 26 || serverIndex == 27 )
		return Config::Get()->EvolveRP.c_str();
	else if ( serverIndex >= 28 && serverIndex <= 30 )
		return Config::Get()->DiamondRP.c_str();
	else if ( serverIndex >= 31 && serverIndex <= 34 )
		return Config::Get()->AdvanceRP.c_str();
	else if ( serverIndex >= 35 && serverIndex <= 37 )
		return Config::Get()->TrinityRP.c_str();
	else if ( serverIndex >= 38 && serverIndex <= 41 )
		return Config::Get()->AbsoluteRP.c_str();
	else if ( serverIndex == 42 )
		return Config::Get()->HMS.c_str();
	else if ( serverIndex == 43 )
		return Config::Get()->SRT.c_str();
	return Config::Get()->Default.c_str();
}
const char* DiscordPresence::GetServerInfo() {
	char* buffer = new char[128];
	sprintf( buffer, "%s", Utility::cp1251ToUTF8( SAMP::Base::CreateInstance()->GetHostname() ).data() );
	return buffer;
}

const char* DiscordPresence::GetWeaponLogo( int weaponIndex ) {
	if ( weaponIndex <= -1 )
		return WeaponLogo[0].data();
	return WeaponLogo[weaponIndex].data();
} 