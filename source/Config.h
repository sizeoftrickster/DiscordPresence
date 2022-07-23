#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <filesystem>
#include <nlohmann/json.hpp>

class Config
{
public:
	struct ConfigData
	{
		// Settings
		int UpdateRate = 2000;
		bool EnablePresence = true;

		// RichPresence
		std::string ApplicationID = "988461715178025021";

		bool EnableShowingTimestamp = true;

		bool EnableShowingActions = true;
		bool EnableShowingGuns = true;
		
		bool EnableShowingFirstButton = true;
		bool EnableShowingSecondButton = true;
		
		std::string FirstButtonText = u8"Прикольный хукер";
		std::string FirstButtonURL = "https://www.blast.hk/threads/101004/";
		std::string SecondButtonText = u8"Лучший биндер";
		std::string SecondButtonURL = "https://www.blast.hk/threads/102157/";

		// ServerLogoNames
		std::string Default = "defaultlogo";
		std::string ArizonaRP = "arizonarplogo";
		std::string SAMPRP = "samprplogo";
		std::string EvolveRP = "evolverplogo";
		std::string DiamondRP = "diamondrplogo";
		std::string AdvanceRP = "advancerplogo";
		std::string TrinityRP = "trinityrplogo";
		std::string AbsoluteRP = "absoluterplogo";
		std::string HMS = "hmslogo";
		std::string SRT = "srteamlogo";

		// MainActionsText
		std::string DisabledActionsText = u8"Шиш вам, а не моя активность!";
		std::string DoesNothing = u8"Ничего не делает =)";
		std::string Running = u8"Летает на ногах =)";

		// ActionsText
		std::string TryingConnection = u8"Подключается к серверу";
		std::string ShowDialog = u8"Просматривает диалог";
		std::string ShowGameText = u8"Просматривает игровой текст";
		std::string ShowTextDraw = u8"Просматривает текстдрав";
		std::string Automobile = u8"Едет в автомобиле";
		std::string MonsterTruck = u8"Едет в монстртраке";
		std::string Quad = u8"Едет на квадроцикле";
		std::string Helicopter = u8"Летит в вертолёте";
		std::string Plane = u8"Летит в самолете";
		std::string Boat = u8"Плывёт на лодке";
		std::string Train = u8"Едет на поезде";
		std::string Bike = u8"Едет на велосипеде/мотоцикле";
		std::string BMX = u8"Едет на БМХ";
	}; // struct ConfigData

	struct WeaponData
	{
		std::string Fist = "fist";
		std::string Brassknuckles = "brassknuckles";
		std::string Golfclub = "golfclub";
		std::string Nightstick = "nightstick";
		std::string Knife = "knife";
		std::string Bat = "bat";
		std::string Shovel = "shovel";
		std::string Poolcue = "poolcue";
		std::string Katana = "katana";
		std::string Chainsaw = "chainsaw";
		std::string Purpledildo = "purpledildo";
		std::string Dildo = "dildo";
		std::string Vibrator = "vibrator";
		std::string Silvervibrator = "silvervibrator";
		std::string Flowers = "flowers";
		std::string Cane = "cane";
		std::string Grenade = "grenade";
		std::string Teargas = "teargas";
		std::string Molotov = "molotov";
		std::string Colt45 = "colt45";
		std::string Silencedpistol = "silencedpistol";
		std::string Deserteagle = "deserteagle";
		std::string Shotgun = "shotgun";
		std::string Sawnoffshotgun = "sawnoffshotgun";
		std::string Combatshotgun = "combatshotgun";
		std::string Uzi = "uzi";
		std::string Mp5 = "mp5";
		std::string Ak47 = "ak47";
		std::string M4 = "m4";
		std::string Tec9 = "tec9";
		std::string Countryrifle = "countryrifle";
		std::string Sniperrifle = "sniperrifle";
		std::string Rocketlauncher = "rocketlauncher";
		std::string Heatseekingrpg = "heatseekingrpg";
		std::string Flamethrower = "flamethrower";
		std::string Minigun = "minigun";
		std::string Satchelcharges = "satchelcharges";
		std::string Detonator = "detonator";
		std::string Spraycan = "spraycan";
		std::string Fireextinguisher = "fireextinguisher";
		std::string Camera = "camera";
		std::string Nightvision = "nightvision";
		std::string Thermalgoggles = "thermalgoggles";
		std::string Parachute = "parachute";
	}; // struct WeaponData

	static void Save();
	static void Load();

	static struct ConfigData* Get();
	static struct WeaponData* GetWeapon();
private:
	static std::filesystem::path GetConfig();
}; // class Config

#endif // !_CONFIG_H_