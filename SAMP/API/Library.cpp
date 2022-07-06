#include "Library.h"
#include <Windows.h>

unsigned long SAMP::GetSAMPHandle() {
	static unsigned long samp{ 0 };
	if ( !samp ) {
		samp = reinterpret_cast<unsigned long>( GetModuleHandleA( "samp" ) );
		if ( !samp || samp == -1 || reinterpret_cast<HANDLE>( samp ) == INVALID_HANDLE_VALUE ) {
			samp = 0;
		}
	}
	return samp;
}

SAMP::sampVersion SAMP::GetSAMPVersion() {
	static sampVersion sampVersion = sampVersion::unknown;
	if ( sampVersion != sampVersion::unknown ) {
		return sampVersion;
	}
	unsigned long samp = GetSAMPHandle();
	if ( !samp ) {
		sampVersion = sampVersion::notLoaded;
	} else {
		unsigned long EntryPoint = reinterpret_cast<IMAGE_NT_HEADERS*>( samp + reinterpret_cast<IMAGE_DOS_HEADER*>( samp )->e_lfanew )->OptionalHeader.AddressOfEntryPoint;
		switch ( EntryPoint ) {
			case ( 0x31DF13 ): {
				sampVersion = sampVersion::R1;
				break;
			}
			case ( 0x3195DD ): {
				sampVersion = sampVersion::R2;
				break;
			}
			case ( 0xCC4D0 ): {
				sampVersion = sampVersion::R3;
				break;
			}
			case ( 0xCBCB0 ): {
				sampVersion = sampVersion::R4;
				break;
			}
			case ( 0xFDB60 ): {
				sampVersion = sampVersion::DL;
				break;
			}
			default: {
				sampVersion = sampVersion::unknown;
				break;
			}
		}
	}
	return sampVersion;
}