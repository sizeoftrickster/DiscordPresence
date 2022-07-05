#ifndef _CLASS_PED_H_
#define _CLASS_PED_H_

#include <Windows.h>
#include <string>

#define PLAYER_PED ( *reinterpret_cast<DWORD*>( 0xB6F5F0 ) )
#define PLAYER_VEHICLE ( *reinterpret_cast<DWORD*>( 0xBA18FC ) )

class CPed
{
	inline static const std::string weaponNames[] =
	{ 
		{ "Fist" },              { "Brass Knuckles" },  { "Golf Club" },       { "Night Stick" },     { "Knife" },        { "Bat" },
		{ "Shovel" },            { "Pool Cue" },        { "Katana" },          { "Chainsaw" },        { "Purple Dildo" }, { "Dildo" },
		{ "Vibrator" },          { "Silver Vibrator" }, { "Flowers" },         { "Cane" },            { "Grenade" },      { "Teargas" },
		{ "Molotov" },           { " " },               { " " },               { " " },               { "Colt 45" },      { "Silenced Pistol" }, 
		{ "Desert Eagle" },      { "Shotgun" },         { "Sawnoff-Shotgun" }, { "Combat Shotgun" },  { "Uzi" },          { "MP5" },
		{ "AK-47" },             { "M4" },              { "Tec-9" },           { "Country Rifle" },   { "Sniper Rifle" }, { "Rocket Launcher" }, 
		{ "Heat-Seeking RPG" },  { "Flamethrower" },    { "Minigun" },         { "Satchel Charges" }, { "Detonator" },    { "Spray Can" },       
		{ "Fire Extinguisher" }, { "Camera" },          { "Night Vision" },    { "Thermal Goggles" }, { "Parachute" }
	};

public:
	enum class PedState : int
	{
		UNKNOWN = -1,
		STAND = 0,
		RUNNING = 1
	}; // enum class PedState
	
	enum class TransportState : int
	{
		UNKNOWN = -1,
		AUTOMOBILE = 0,
		MTRUCK = 1,
		QUAD = 2,
		HELICOPTER = 3,
		PLANE = 4,
		BOAT = 5,
		TRAIN = 6,
		BIKE = 7,
		BMX = 8
	}; // enum class TransportState

	static bool IsPedAvailable();
	
	/*
		CPed +0x530 = Статус: 
		0 = покидает машину, падает с байка или что-то в этом роде
		1 = нормальный случай
		50 = водит
		54 = игрок только-что умер (записи wasted ещё не видно)
		55 = погиб
		63 = арестован
	*/
	static int GetPedStatus();
	/*
		CPed +0x534 = Статус бега:
			0 = пока водит
			1 = неподвижно стоит
			4 = начинает бежать
			6 = бежит
			7 = спринт (бежит с ускорением) 
	*/
	static int GetPedRunningState();

	static bool IsPedDriving();
	static TransportState GetTransportState();

	static PedState GetPedRunningStatus();

	static int GetPedWeaponId();
	static std::pair<int, std::string> GetWeaponInfo();
}; // class CPed

#endif // !_CLASS_PED_H_