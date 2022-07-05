#include "Pools.h"
#include "Library.h"
#include "PlayerPool.h"

SAMP::Pools::Pools( void* pPools_ ) : pPools( pPools_ ) {
	switch ( GetSAMPVersion() ) {
		case ( sampVersion::R1 ): {
			ppPlayer = reinterpret_cast<void**>( (size_t)pPools + 0x18 );
			break;
		}
		case ( sampVersion::R2 ): {
			ppPlayer = reinterpret_cast<void**>( (size_t)pPools + 0x8 );
			break;
		}
		case ( sampVersion::R3 ): {
			ppPlayer = reinterpret_cast<void**>( (size_t)pPools + 0x8 );
			break;
		}
		/*case (sampVersion::R4): {
			ppPlayer = reinterpret_cast<void**>((size_t)pPools + 0x8);
			break;
		} */
		default: {
			break;
		}
	}
}

SAMP::Pools::~Pools() {
	if ( pPlayers_ ) {
		delete pPlayers_;
		pPlayers_ = nullptr;
	}
}

SAMP::PlayerPool* SAMP::Pools::PlayerPool() {
	if (*ppPlayer != nullptr) {
		if (!pPlayers_) pPlayers_ = new SAMP::PlayerPool( *ppPlayer );
		return pPlayers_;
	}
	return nullptr;
}