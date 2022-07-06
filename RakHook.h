#ifndef _RAK_HOOK_H_
#define _RAK_HOOK_H_

#include <lemon/detour.hpp>

#include "RakNet/BitStream.h"
#include "RakNet/PacketEnumerations.h"

// char __thiscall sub_00000000( char *this, _BYTE *a2, int output, int a4, __int16 a5 )
using RPCIncomingHandlerPrototype = char( __thiscall* )( void*, const char*, int, PlayerID );
// int __thiscall sub_00000000( char *this )
using PacketsIncomingHandlerPrototype = Packet*( __thiscall* )( void* );

class RakHook
{
	static constexpr int MAX_ALLOCA_STACK_ALLOCATION{ 1048576 };
	
	void* pIncomingRPC{ nullptr };
	void* pIncomingPackets{ nullptr };

	lemon::detour<RPCIncomingHandlerPrototype> incomingRpcHook_{ 0x0 };
	lemon::detour<PacketsIncomingHandlerPrototype> incomingPacketsHook_{ 0x0 };
public:
	enum class RPCActions : int
	{
		DOES_NOTHING = 0,
		SHOW_DIALOG = 1,
		SHOW_GAMETEXT = 2,
		SHOW_TEXTDRAW = 3
	}; // enum class RPCAction
	enum class PacketsActions : int
	{
		DOES_NOTHING = 0,
		TRYING_CONNECTION = 1
	}; // enum class PacketsAction

	RakHook();
	~RakHook();

	static RPCActions GetRPCAction();
	static PacketsActions GetPacketsAction();
private:
	unsigned char readPacketId( RakNet::BitStream BitStream );

	char RPCIncomingHandlerHooked( RPCIncomingHandlerPrototype fpHkOriginal, void* _this, const char* data, int length, PlayerID playerId );
	Packet* PacketsIncomingHandlerHooked( PacketsIncomingHandlerPrototype fpHkOriginal, void* _this );
}; // class RakHook

#endif // !_RAK_HOOK_H_