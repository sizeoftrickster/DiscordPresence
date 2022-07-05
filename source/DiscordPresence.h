#ifndef _DISCORD_PRESENCE_H_
#define _DISCORD_PRESENCE_H_

#include <string>
#include <vector>
#include <ctime>
#include <memory>

class DiscordPresence 
{
	std::unique_ptr<class RakHook> rpcHook_;
	time_t Timestamp = std::time( 0 );

	std::string applicationId = "988461715178025021";
	
	std::vector<std::string> ServersIP = {
//		Phoenix[0]         Tucson[1]          Scottdale[2]       Chandler[3]        Brainburg[4]             
		"185.169.134.3",   "185.169.134.4",   "185.169.134.43",  "185.169.134.44",  "185.169.134.45",
//      Saint-Rose[5]      Mesa[6]            Red-Rock[7]        Yuma[8]            Surprise[9]
		"185.169.134.5",   "185.169.134.59",  "185.169.134.61",  "185.169.134.107", "185.169.134.109",
//      Prescott[10]       Glendale[11]       Kingman[12]        Winslow[13]        Payson[14]
		"185.169.134.166", "185.169.134.171", "185.169.134.172", "185.169.134.173", "185.169.134.174",
//      Gilbert[15]        Show-Low[16]       Casa-Grande[17]    Page[18]           Sun-City[19]
		"80.66.82.191",    "80.66.82.190",    "80.66.82.188",    "80.66.82.168",    "80.66.82.159",
//      Queen-Creek[20]
		"80.66.82.200",

//      Server02[21]   Revolution[22] Classic[23]    Legacy[24]
		"92.63.199.5", "92.63.199.6", "92.63.199.7", "92.63.199.8",

//      Saint-Louis[25]   Cleveland[26]
		"185.169.134.67", "185.169.134.91",

//		Trilliant[27]   Emerald[28]      Ruby[29]
		"51.75.33.152", "51.83.207.240", "51.83.207.243",

//		Red[30]         Green[31]       Blue[32]        Lime[33]
		"54.37.142.72", "54.37.142.73", "54.37.142.74", "54.37.142.75",

//      RPG[34]           One[35]           Two[36]
		"185.169.134.83", "185.169.134.84", "185.169.134.85",

//		HMS[37]          SRC[38]
		"185.189.15.89", "51.15.108.122"
	};

	std::vector<std::string> WeaponLogo = {
		{ "fist" },             { "brassknuckles" },  { "golfclub" },       { "nightstick" },     { "knife" },       { "bat" },
		{ "shovel" },           { "poolcue" },        { "katana" },         { "chainsaw" },       { "purpledildo" }, { "dildo" },
		{ "vibrator" },         { "silvervibrator" }, { "flowers" },        { "cane" },           { "grenade" },     { "teargas" },
		{ "molotov" },          { " " },              { " " },              { " " },              { "colt45" },      { "silencedpistol" },
		{ "deserteagle" },      { "shotgun" },        { "sawnoffshotgun" }, { "combatshotgun" },  { "uzi" },         { "mp5" },
		{ "ak47" },             { "m4" },             { "tec9" },           { "countryrifle" },   { "sniperrifle" }, { "rocketlauncher" }, 
		{ "heatseekingrpg" },   { "flamethrower" },   { "minigun" },        { "satchelcharges" }, { "detonator" },   { "spraycan" },       
		{ "fireextinguisher" }, { "camera" },         { "nightvision" },    { "thermalgoggles" }, { "parachute" }
	};
public:
	DiscordPresence();
	~DiscordPresence();

	void Update();
protected:
	int GetServerIndex( const char* serverAddress );
	
	const char* GetPlayerState();
	const char* GetPlayerDetails();

	const char* GetServerLogo( int serverIndex );
	const char* GetServerInfo();

	const char* GetWeaponLogo( int weaponIndex );
}; // class DiscordPresence 

#endif // !_DISCORD_PRESENCE_H_