#include "CPed.h"

bool CPed::IsPedAvailable() {
	if ( !PLAYER_PED )
		return false;
	return true;
}

int CPed::GetPedStatus() {
	if ( !IsPedAvailable() )
		return -1;
	return *reinterpret_cast<int*>( PLAYER_PED + 0x530 );
}

int CPed::GetPedRunningState() {
	if ( !IsPedAvailable() )
		return -1;
	return *reinterpret_cast<int*>( PLAYER_PED + 0x534 );
}

CPed::PedState CPed::GetPedRunningStatus() {
	if ( !IsPedAvailable() || GetPedRunningState() == -1 )
		return PedState::UNKNOWN;

	static PedState pedState = PedState::UNKNOWN;
	auto pedRunningState = GetPedRunningState();

	if ( pedRunningState == 0 || pedRunningState == 1 )
		pedState = PedState::STAND;
	else if ( pedRunningState == 4 || pedRunningState == 6 || pedRunningState == 7 )
		pedState = PedState::RUNNING;

	return pedState;
}

bool CPed::IsPedDriving() {
	return GetPedStatus() == 50 || GetPedStatus() == 0;
}

CPed::TransportState CPed::GetTransportState() {
	if ( !IsPedDriving() || !PLAYER_VEHICLE )
		return TransportState::UNKNOWN;

	static TransportState transportState = TransportState::UNKNOWN;
	auto VehicleSubClass = *reinterpret_cast<DWORD*>( PLAYER_VEHICLE + 0x594 );

	switch ( VehicleSubClass ) {
		// CAutomobile
		case ( 0 ): {
			transportState = TransportState::AUTOMOBILE;
			break;
		}
		// CMtruck
		case ( 1 ): {
			transportState = TransportState::MTRUCK;
			break;
		}
		// CQuad
		case ( 2 ): {
			transportState = TransportState::QUAD;
			break;
		}
		// CHeli
		case ( 3 ): {
			transportState = TransportState::HELICOPTER;
			break;
		}
		// CPlane
		case ( 4 ): {
			transportState = TransportState::PLANE;
			break;
		}
		// CBoat
		case ( 5 ): {
			transportState = TransportState::BOAT;
			break;
		}
		// CTrain
		case ( 6 ): {
			transportState = TransportState::TRAIN;
			break;
		}
		// CBike
		case ( 9 ): {
			transportState = TransportState::BIKE;
			break;
		}
		// CBMX
		case ( 10 ): {
			transportState = TransportState::BMX;
			break;
		}
		// CTrailer
		case ( 11 ): {
			transportState = TransportState::AUTOMOBILE;
			break;
		}
		default: {
			break;
		}
	}

	return transportState;
}

int CPed::GetPedWeaponId() {
	if ( !IsPedAvailable() )
		return -1;
	return *reinterpret_cast<int*>( 0xBAA410 );
}

std::pair<int, std::string> CPed::GetWeaponInfo() {
	int weaponIndex = GetPedWeaponId();
	std::string weaponName = "Fist";
	if ( weaponIndex >= 0 && weaponIndex <= 49 )
		weaponName = weaponNames[weaponIndex];
	return std::make_pair( weaponIndex, weaponName );
}