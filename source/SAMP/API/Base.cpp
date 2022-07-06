#include "Base.h"
#include "Library.h"
#include "Pools.h"
#include <iostream>

SAMP::Base* SAMP::Base::self{ nullptr };

SAMP::Base::Base() {
	switch ( GetSAMPVersion() ) {
		case ( sampVersion::R1 ): {
			pSAMP = *reinterpret_cast<void**>( GetSAMPHandle() + 0x21A0F8 );
			ppPools = reinterpret_cast<void**>( (size_t)pSAMP + 0x3CD );
			ofHostName = 0x121;
			ofAddress = 0x20;
			ofPort = 0x225;
			break;
		}
		case ( sampVersion::R2 ): {
			pSAMP = *reinterpret_cast<void**>( GetSAMPHandle() + 0x21A100 );
			ppPools = reinterpret_cast<void**>( (size_t)pSAMP + 0x3C5 );
			ofHostName = 0x11D;
			ofAddress = 0x1C;
			ofPort = 0x221;
			break;
		}
		case ( sampVersion::R3 ): {
			pSAMP = *reinterpret_cast<void**>( GetSAMPHandle() + 0x26E8DC );
			ppPools = reinterpret_cast<void**>( (size_t)pSAMP + 0x3DE );
			ofHostName = 0x131;
			ofAddress = 0x30;
			ofPort = 0x235;
			break;
		}
		/*case (sampVersion::R4): {
			pSAMP = *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EA0C);
			ppPools = reinterpret_cast<void**>( (size_t)pSAMP + 0x3DE );
			ofHostName = 0x131;
			ofAddress = 0x30;
			ofPort = 0x235;
			break;
		} */
		case ( sampVersion::DL ): {
			pSAMP = *reinterpret_cast<void**>( GetSAMPHandle() + 0x2ACA24 );
			ppPools = reinterpret_cast<void**>( (size_t)pSAMP + 0x3DE );
			ofHostName = 0x131;
			ofAddress = 0x30;
			ofPort = 0x235;
			break;
		}
		default: {
			break;
		}
	}
}

SAMP::Base::~Base() {
	if ( pPools_ ) {
		delete pPools_;
		pPools_ = nullptr;
	}
}

SAMP::Base* SAMP::Base::CreateInstance() {
	if ( !self )
		self = new Base();
	return self;
}

void SAMP::Base::DeleteInstance() {
	if ( self ) {
		delete self;
		self = nullptr;
	}
}

bool SAMP::Base::isSAMPInitilize() {
	if ( GetSAMPVersion() == sampVersion::R1 )
		return *reinterpret_cast<void**>( GetSAMPHandle() + 0x21A0F8 ) != nullptr;
	else if ( GetSAMPVersion() == sampVersion::R2 )
		return *reinterpret_cast<void**>( GetSAMPHandle() + 0x21A100 ) != nullptr;
	else if ( GetSAMPVersion() == sampVersion::R3 )
		return *reinterpret_cast<void**>( GetSAMPHandle() + 0x26E8DC ) != nullptr;
	/*else if (GetSAMPVersion() == sampVersion::R4)
		return *reinterpret_cast<void**>( GetSAMPHandle() + 0x26EA0C ) != nullptr; */
	else if ( GetSAMPVersion() == sampVersion::DL )
		return *reinterpret_cast<void**>( GetSAMPHandle() + 0x2ACA24 ) != nullptr;
	return false;
}

SAMP::Pools* SAMP::Base::Pools() {
	if ( ppPools != nullptr ) {
		if (*ppPools != nullptr) {
			if (!pPools_) pPools_ = new SAMP::Pools(*ppPools);
			return pPools_;
		}
	}
	return nullptr;
}

const char* SAMP::Base::GetHostname() {
	if ( !pSAMP )
		return nullptr;
	return reinterpret_cast<const char*>( (size_t)pSAMP + ofHostName );
}

const char* SAMP::Base::GetServerIP() {
	if ( !pSAMP )
		return nullptr;
	return reinterpret_cast<const char*>( (size_t)pSAMP + ofAddress );
}

short SAMP::Base::GetServerPort() {
	if ( !pSAMP )
		return -1;
	return *reinterpret_cast<short*>( (size_t)pSAMP + ofPort );
}

char* SAMP::Base::GetServer() {
	char* Buffer = new char[128];
	sprintf( Buffer, "%s:%d", GetServerIP(), GetServerPort() );
	return Buffer;
}