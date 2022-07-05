#include "RakHook.h"
#include "SAMP/samp.hpp"
#include "Utility.h"
#include "Config.h"

RakHook::RPCActions RPCAction = RakHook::RPCActions::DOES_NOTHING;
RakHook::PacketsActions PacketsAction = RakHook::PacketsActions::DOES_NOTHING;

template<typename result, typename source>
result pointer_cast(source* v) {
	return static_cast<result>(static_cast<void*>(v));
}

template<typename result, typename source>
result pointer_cast(const source* v) {
	return static_cast<result>(static_cast<const void*>(v));
}

RakHook::RakHook() {
	switch ( SAMP::GetSAMPVersion() ) {
		case ( SAMP::sampVersion::R1 ): {
			pIncomingRPC = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x372F0 );
			pIncomingPackets = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x31180 );
			break;
		}
		case ( SAMP::sampVersion::R2 ): {
			pIncomingRPC = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x373D0 );
			pIncomingPackets = reinterpret_cast<void*>(SAMP::GetSAMPHandle() + 0x31180 );
			break;
		}
		case ( SAMP::sampVersion::R3 ): {
			pIncomingRPC = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x3A6A0 );
			pIncomingPackets = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x31CA0 );
			break;
		}
		/*case (SAMP::sampVersion::R4): {
			pIncomingRPC = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x3ADE0 );
			pIncomingPackets = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x31CA0 );
			break;
		} */
		default: {
			break;
		}
	}

	if ( !pIncomingRPC || !pIncomingPackets )
		return;

	incomingRpcHook_.set_addr( reinterpret_cast<uintptr_t>( pIncomingRPC ) );
	incomingPacketsHook_.set_addr( reinterpret_cast<uintptr_t>( pIncomingPackets ) );

	incomingRpcHook_.install( std::make_tuple( this, &RakHook::RPCIncomingHandlerHooked ) );
	incomingPacketsHook_.install( std::make_tuple( this, &RakHook::PacketsIncomingHandlerHooked ) );
}

RakHook::~RakHook() {
	incomingPacketsHook_.remove();
	incomingRpcHook_.remove();
}

RakHook::RPCActions RakHook::GetRPCAction() {
	return RPCAction;
}

RakHook::PacketsActions RakHook::GetPacketsAction() {
	return PacketsAction;
}

unsigned char RakHook::readPacketId( RakNet::BitStream BitStream ) {
	unsigned char value;
	BitStream.Read( value );
	return value;
}

char RakHook::RPCIncomingHandlerHooked( RPCIncomingHandlerPrototype fpHkOriginal, void* _this, const char* data, int length, PlayerID playerId ) {
	RakNet::BitStream BitStream( pointer_cast<unsigned char*>( const_cast<char*>( data ) ), length, true );
	unsigned char ID{ 0 };
	unsigned char* InputData{ nullptr };
	unsigned int BitsData{ 0 };
	std::shared_ptr<RakNet::BitStream> CallbackBS = std::make_shared<RakNet::BitStream>();

	BitStream.IgnoreBits( 8 );
	if ( data[0] == ID_TIMESTAMP )
		BitStream.IgnoreBits( 8 * ( sizeof( RakNetTime ) + sizeof( unsigned char ) ) );

	int Offset = BitStream.GetReadOffset();
	BitStream.Read( ID );

	if ( !BitStream.ReadCompressed( BitsData ) )
		return false;

	if ( BitsData ) {
		bool usedAlloca{ false };
		if ( BITS_TO_BYTES( BitStream.GetNumberOfUnreadBits() ) < MAX_ALLOCA_STACK_ALLOCATION ) {
			InputData = pointer_cast<unsigned char*>( alloca( BITS_TO_BYTES( BitStream.GetNumberOfUnreadBits() ) ) );
			usedAlloca = true;
		} else {
			InputData = new unsigned char[BITS_TO_BYTES(BitStream.GetNumberOfUnreadBits())];
		}

		if ( !BitStream.ReadBits( InputData, BitsData, false ) )
			return false;

		CallbackBS = std::make_shared<RakNet::BitStream>( InputData, BITS_TO_BYTES( BitsData ), true );

		if ( !usedAlloca )
			delete[] InputData;
	}

	switch ( ID ) {
		// ShowDialog //
		case ( 61 ): {
			RPCAction = RPCActions::SHOW_DIALOG;
			break;
		}
		// ShowGameText //
		case ( 73 ): {
			RPCAction = RPCActions::SHOW_GAMETEXT;
			break;
		}
		// ShowTextDraw //
		case ( 134 ): {
			RPCAction = RPCActions::SHOW_TEXTDRAW;
			break;
		}
		default: {
			RPCAction = RPCActions::DOES_NOTHING;
			break;
		}
	}

	BitStream.SetWriteOffset( Offset );
	BitStream.Write( ID );
	BitsData = BYTES_TO_BITS( CallbackBS->GetNumberOfBytesUsed() );
	BitStream.WriteCompressed( BitsData );
	if ( BitsData )
		BitStream.WriteBits( CallbackBS->GetData(), BitsData, false );

	return fpHkOriginal( _this, pointer_cast<char*>( BitStream.GetData() ), BitStream.GetNumberOfBytesUsed(), playerId );
}

Packet* RakHook::PacketsIncomingHandlerHooked( PacketsIncomingHandlerPrototype fpHkOriginal, void* this_ ) {
	Packet* Packet = fpHkOriginal( this_ );
	if ( Packet == nullptr || Packet->bitSize == 0 || Packet->data == nullptr || Packet->length == 0 )
		return Packet;

	RakNet::BitStream BitStream( Packet->data, BITS_TO_BYTES( Packet->length ), false );
	
	unsigned char PacketID = RakHook::readPacketId( BitStream );
	
	switch ( PacketID ) {
		// ID_NO_FREE_INCOMING_CONNECTIONS // 
		case ( 31 ): {
			PacketsAction = RakHook::PacketsActions::TRYING_CONNECTION;
			break;
		}
		default: {
			PacketsAction = RakHook::PacketsActions::DOES_NOTHING;
			break;
		}
	}

	return Packet;
}