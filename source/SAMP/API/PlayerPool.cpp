#include "PlayerPool.h"
#include "Library.h"

SAMP::PlayerPool::PlayerPool( void* pPlayerPool ) : pPlayerPool( pPlayerPool ) {
	switch ( GetSAMPVersion() ) {
		case ( sampVersion::R1 ): {
			pLocalPlayerNickname = reinterpret_cast<void*>( (size_t)pPlayerPool + 0xA );
			pLocalPlayerId = reinterpret_cast<short*>( (size_t)pPlayerPool + 0x4 );
			break;
		}
		case ( sampVersion::R2 ): {
			pLocalPlayerNickname = reinterpret_cast<void*>( (size_t)pPlayerPool + 0x6 );
			pLocalPlayerId = reinterpret_cast<short*>( (size_t)pPlayerPool + 0x0 );
			break;
		}
		case ( sampVersion::R3 ): {
			pLocalPlayerNickname = reinterpret_cast<void*>( (size_t)pPlayerPool + 0x2F22 );
			pLocalPlayerId = reinterpret_cast<short*>( (size_t)pPlayerPool + 0x2F1C );
			break;
		}
		default: {
			break;
		}
	}
}


short SAMP::PlayerPool::GetLocalPlayerId() {
	if (pLocalPlayerId) return *pLocalPlayerId;
	return -1;
}


std::string SAMP::PlayerPool::GetLocalPlayerNickname() {
	struct msvc_string {
		union {
			char  szString[0x10];
			char* pszString;
		};
		std::size_t length;
		std::size_t allocated;
	};
	auto string = *reinterpret_cast<msvc_string*>(pLocalPlayerNickname);
	if (string.allocated < 0x10) return { string.szString, string.length };
	return { string.pszString, string.length };
}