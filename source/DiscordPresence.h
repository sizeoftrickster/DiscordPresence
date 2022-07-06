#ifndef _DISCORD_PRESENCE_H_
#define _DISCORD_PRESENCE_H_

#include <string>
#include <vector>
#include <ctime>
#include <memory>

class DiscordPresence 
{
	std::unique_ptr<class RakHook> RpcHook_;

	std::string applicationId = "988461715178025021";
	time_t Timestamp = std::time( 0 );
	
	std::vector<std::string> ServersIP = {
//		Phoenix[0]            Tucson[1]             Scottdale[2]           Chandler[3]            Brainburg[4]             
		"185.169.134.3:7777", "185.169.134.4:7777", "185.169.134.43:7777", "185.169.134.44:7777", "185.169.134.45:7777",
//      Saint-Rose[5]         Mesa[6]           Red-Rock[7]            Yuma[8]                 Surprise[9]
		"185.169.134.5:7777", "185.169.134.59", "185.169.134.61:7777", "185.169.134.107:7777", "185.169.134.109:7777",
//      Prescott[10]            Glendale[11]            Kingman[12]             Winslow[13]             Payson[14]
		"185.169.134.166:7777", "185.169.134.171:7777", "185.169.134.172:7777", "185.169.134.173:7777", "185.169.134.174:7777",
//      Gilbert[15]          Show-Low[16]         Casa-Grande[17]      Page[18]             Sun-City[19]
		"80.66.82.191:7777", "80.66.82.190:7777", "80.66.82.188:7777", "80.66.82.168:7777", "80.66.82.159:7777",
//      Queen-Creek[20] Sedona[21]
		"80.66.82.200", "80.66.82.144",

//      Server02[22]        Revolution[23]      Classic[24]         Legacy[25]
		"92.63.199.5:7777", "92.63.199.6:7777", "92.63.199.7:7777", "92.63.199.8:7777",

//      Saint-Louis[26]        Cleveland[27]
		"185.169.134.67:7777", "185.169.134.91:7777",

//		Trilliant[28]        Emerald[29]           Ruby[30]
		"51.75.33.152:7777", "51.83.207.240:7777", "51.83.207.243:7777",

//		Red[31]              Green[32]            Blue[33]             Lime[34]
		"54.37.142.72:7777", "54.37.142.73:7777", "54.37.142.74:7777", "54.37.142.75:7777",

//      RPG[35]                One[36]                Two[37]
		"185.169.134.83:7777", "185.169.134.84:7777", "185.169.134.85:7777",

//      Lithium[38]          Chromium[39]         Titanium[40]         Aurum[41]
		"193.84.90.23:7775", "193.84.90.23:7773", "193.84.90.23:7772", "193.84.90.23:7774",

//		HMS[42]               SRC[43]
		"185.189.15.89:7228", "51.15.108.122:1337"
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