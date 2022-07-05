#include "DiscordPresence.h"
#include "Discord/discord-rpc.h"
#include "SAMP/samp.hpp"
#include "GTA/game.hpp"
#include "Utility.h"
#include "RakHook.h"
#include "Config.h"

/*
	Прежде чем говорить, почему нельзя было передать в структуру через .c_str() или .data(), сам вахуй, что эта еще та баганная хуйня, и она
	артефачит как тварь, показывая не те данные. Именно поэтому я использовал sprintf().

	Некорректная Работа:
	richPresence.state = SomeData().data(); || richPresence.state = SomeData().c_str();

	Корректная Работа:
	char* buf = new char[128];
	sprintf( "%s", SomeData().data() ); 
	richPresence.state = buf;

	Интересный момент, это действует только на данные объекты: state, details, largeImageKey, smallImageKey.
*/

DiscordPresence::DiscordPresence() {
	DiscordEventHandlers eventHandler;
	memset( &eventHandler, 0, sizeof( eventHandler ) );
	Discord_Initialize( applicationId.c_str(), &eventHandler, NULL, NULL );
	rpcHook_ = std::make_unique<RakHook>();
}

DiscordPresence::~DiscordPresence() {
	Discord_Shutdown();
}

void DiscordPresence::Update() {
	DiscordRichPresence richPresence;
	memset( &richPresence, 0, sizeof( richPresence ) );

	int serverIndex = GetServerIndex( SAMP::Base::CreateInstance()->GetServerIP() );
	auto [weaponIndex, weaponName] = CPed::GetWeaponInfo();

	// Info //
	richPresence.state = GetPlayerState();
	richPresence.details = GetPlayerDetails();
	// ServerLogo //
	richPresence.largeImageKey = GetServerLogo( serverIndex );
	richPresence.largeImageText = GetServerInfo();
	// WeaponLogo //
	richPresence.smallImageKey = GetWeaponLogo( weaponIndex );
	richPresence.smallImageText = weaponName.data();
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
	char* buffer = new char[128];
	const char* FinalAction = Config::Get()->DoesNothing.data();

	switch ( RakHook::GetPacketsAction() ) {
		case ( RakHook::PacketsActions::TRYING_CONNECTION ): {
			FinalAction = Config::Get()->TryingConnection.data();
			break;
		}
		case ( RakHook::PacketsActions::DOES_NOTHING ): {
			switch ( RakHook::GetRPCAction() ) {
				case ( RakHook::RPCActions::SHOW_DIALOG ): {
					FinalAction = Config::Get()->ShowDialog.data();
					break;
				}
				case ( RakHook::RPCActions::SHOW_TEXTDRAW ): {
					FinalAction = Config::Get()->ShowTextDraw.data();
					break;
				}
				case ( RakHook::RPCActions::SHOW_GAMETEXT ): {
					FinalAction = Config::Get()->ShowGameText.data();
					break;
				}
				case ( RakHook::RPCActions::DOES_NOTHING ): {	
					switch ( CPed::GetTransportState() ) {
						case ( CPed::TransportState::AUTOMOBILE ): {
							FinalAction = Config::Get()->Automobile.data();
							break;
						}
						case ( CPed::TransportState::MTRUCK ): {
							FinalAction = Config::Get()->MonsterTruck.data();
							break;
						}
						case ( CPed::TransportState::QUAD ): {
							FinalAction = Config::Get()->Quad.data();
							break;
						}
						case ( CPed::TransportState::HELICOPTER ): {
							FinalAction = Config::Get()->Helicopter.data();
							break;
						}
						case ( CPed::TransportState::PLANE ): {
							FinalAction = Config::Get()->Plane.data();
							break;
						}
						case ( CPed::TransportState::BOAT ): {
							FinalAction = Config::Get()->Boat.data();
							break;
						}
						case ( CPed::TransportState::TRAIN ): {
							FinalAction = Config::Get()->Train.data();
							break;
						}
						case ( CPed::TransportState::BIKE ): {
							FinalAction = Config::Get()->Bike.data();
							break;
						}
						case ( CPed::TransportState::BMX ): {
							FinalAction = Config::Get()->BMX.data();
							break;
						}
						case ( CPed::TransportState::UNKNOWN ): {
							switch ( CPed::GetPedRunningStatus() ) {
								case ( CPed::PedState::RUNNING ): {
									FinalAction = Config::Get()->Running.data();
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

	sprintf( buffer, "%s", Utility::cp1251ToUTF8( Utility::utf8ToCp1251( FinalAction ).data() ).data() );

	return buffer;
}
const char* DiscordPresence::GetPlayerDetails() {
	char* buffer = new char[128];
	auto playerPool = SAMP::Base::CreateInstance()->Pools()->PlayerPool();
	sprintf( buffer, "%s[%d]", Utility::cp1251ToUTF8( playerPool->GetLocalPlayerNickname().data() ).data(), playerPool->GetLocalPlayerId() );
	return buffer;
}

const char* DiscordPresence::GetServerLogo( int serverIndex ) {
	if ( serverIndex >= 0 && serverIndex <= 20 )
		return "arizonarplogo";
	else if ( serverIndex >= 21 && serverIndex <= 24 )
		return "samprplogo";
	else if ( serverIndex == 25 || serverIndex == 26 )
		return "evolverplogo";
	else if ( serverIndex >= 27 && serverIndex <= 29 )
		return "diamondrplogo";
	else if ( serverIndex >= 30 && serverIndex <= 33 )
		return "advancerplogo";
	else if ( serverIndex >= 34 && serverIndex <= 36 )
		return "trinityrplogo";
	else if ( serverIndex == 37 )
		return "hmslogo";
	else if ( serverIndex == 38 )
		return "srteamlogo";
	return "defaultlogo";
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

/*
const char* Action = Config::Get()->DoesNothing.data();
	CPed::TransportState VehState = CPed::GetTransportState();
	RakHook::RPCAction RPCAction = RakHook::GetRPCAction();

	if ( RPCAction != RakHook::RPCAction::DOES_NOTHING ) {
		switch ( RPCAction ) {
			case ( RakHook::RPCAction::SHOW_DIALOG ): {
				Action = Config::Get()->ShowDialog.data();
				break;
			}
			case ( RakHook::RPCAction::SHOW_TEXTDRAW ): {
				Action = Config::Get()->ShowTextDraw.data();
				break;
			}
			case ( RakHook::RPCAction::SHOW_GAMETEXT ): {
				Action = Config::Get()->ShowGameText.data();
				break;
			}
		}
	} else {
		switch ( VehState ) {
			case ( CPed::TransportState::UNKNOWN ): {

				CPed::PedState RunningState = CPed::GetPedRunningStatus();
				if ( RunningState == CPed::PedState::RUNNING )
					Action = Config::Get()->Running.data();

				break;
			}
			case ( CPed::TransportState::AUTOMOBILE ): {
				Action = Config::Get()->Automobile.data();
				break;
			}
			case ( CPed::TransportState::MTRUCK ): {
				Action = Config::Get()->MonsterTruck.data();
				break;
			}
			case ( CPed::TransportState::QUAD ): {
				Action = Config::Get()->Quad.data();
				break;
			}
			case ( CPed::TransportState::HELICOPTER ): {
				Action = Config::Get()->Helicopter.data();
				break;
			}
			case ( CPed::TransportState::PLANE ): {
				Action = Config::Get()->Plane.data();
				break;
			}
			case ( CPed::TransportState::BOAT ): {
				Action = Config::Get()->Boat.data();
				break;
			}
			case ( CPed::TransportState::TRAIN ): {
				Action = Config::Get()->Train.data();
				break;
			}
			case ( CPed::TransportState::BIKE ): {
				Action = Config::Get()->Bike.data();
				break;
			}
			case ( CPed::TransportState::BMX ): {
				Action = Config::Get()->BMX.data();
				break;
			}
		}
	}
*/