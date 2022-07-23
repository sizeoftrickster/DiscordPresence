#include "Config.h"
#include <Windows.h>
#include <fstream>
#include "Utility.h"

struct Config::ConfigData ConfigData_;
struct Config::WeaponData WeaponData_;

struct Config::ConfigData* Config::Get() {
	return &ConfigData_;
}

void Config::Save() {
	nlohmann::ordered_json json;

	// Settings
	json["Settings"]["UpdateRate"] = ConfigData_.UpdateRate;
	json["Settings"]["EnablePresence"] = ConfigData_.EnablePresence;

	// RichPresence
	json["RichPresence"]["ApplicationID"] = ConfigData_.ApplicationID;
	json["RichPresence"]["EnableShowingTimestamp"] = ConfigData_.EnableShowingTimestamp;
	json["RichPresence"]["EnableShowingActions"] = ConfigData_.EnableShowingActions;
	json["RichPresence"]["EnableShowingGuns"] = ConfigData_.EnableShowingGuns;
	json["RichPresence"]["EnableShowingFirstButton"] = ConfigData_.EnableShowingFirstButton;
	json["RichPresence"]["EnableShowingSecondButton"] = ConfigData_.EnableShowingSecondButton;
	json["RichPresence"]["FirstButtonText"] = ConfigData_.FirstButtonText;
	json["RichPresence"]["FirstButtonURL"] = ConfigData_.FirstButtonURL;
	json["RichPresence"]["SecondButtonText"] = ConfigData_.SecondButtonText;
	json["RichPresence"]["SecondButtonURL"] = ConfigData_.SecondButtonURL;

	// ServerLogoNames
	json["ServerLogoNames"]["Default"] = ConfigData_.Default;
	json["ServerLogoNames"]["ArizonaRP"] = ConfigData_.ArizonaRP;
	json["ServerLogoNames"]["SAMPRP"] = ConfigData_.SAMPRP;
	json["ServerLogoNames"]["EvolveRP"] = ConfigData_.EvolveRP;
	json["ServerLogoNames"]["DiamondRP"] = ConfigData_.DiamondRP;
	json["ServerLogoNames"]["AdvanceRP"] = ConfigData_.AdvanceRP;
	json["ServerLogoNames"]["TrinityRP"] = ConfigData_.TrinityRP;
	json["ServerLogoNames"]["AbsoluteRP"] = ConfigData_.AbsoluteRP;
	json["ServerLogoNames"]["HackMySoftware"] = ConfigData_.HMS;
	json["ServerLogoNames"]["SR_team"] = ConfigData_.SRT;

	// MainActions
	json["MainActionsText"]["DisabledActionsText"] = ConfigData_.DisabledActionsText;
	json["MainActionsText"]["DoesNothing"] = ConfigData_.DoesNothing;
	json["MainActionsText"]["Running"] = ConfigData_.Running;

	// Actions
	json["ActionsText"]["TryingConnection"] = ConfigData_.TryingConnection;
	json["ActionsText"]["ShowDialog"] = ConfigData_.ShowDialog;
	json["ActionsText"]["ShowGameText"] = ConfigData_.ShowGameText;
	json["ActionsText"]["ShowTextDraw"] = ConfigData_.ShowTextDraw;
	json["ActionsText"]["Automobile"] = ConfigData_.Automobile;
	json["ActionsText"]["MonsterTruck"] = ConfigData_.MonsterTruck;
	json["ActionsText"]["Quad"] = ConfigData_.Quad;
	json["ActionsText"]["Helicopter"] = ConfigData_.Helicopter;
	json["ActionsText"]["Plane"] = ConfigData_.Plane;
	json["ActionsText"]["Boat"] = ConfigData_.Boat;
	json["ActionsText"]["Train"] = ConfigData_.Train;
	json["ActionsText"]["Bike"] = ConfigData_.Bike;
	json["ActionsText"]["BMX"] = ConfigData_.BMX;

	std::ofstream( GetConfig().string() ) << json.dump( 4 );
}

void Config::Load() {
	std::ifstream config( GetConfig().string() );
	if ( !config.is_open() ) {
		return Save();
	}

	try {
		std::string content = std::string( ( std::istreambuf_iterator<char>( config ) ), std::istreambuf_iterator<char>() );
		auto json = nlohmann::json::parse( content );
		
		// Settings
		json["Settings"]["UpdateRate"].get_to<int>( ConfigData_.UpdateRate );
		json["Settings"]["EnablePresence"].get_to<bool>( ConfigData_.EnablePresence );

		// RichPresence
		json["RichPresence"]["ApplicationID"].get_to<std::string>( ConfigData_.ApplicationID );
		json["RichPresence"]["EnableShowingTimestamp"].get_to<bool>( ConfigData_.EnableShowingTimestamp );
		json["RichPresence"]["EnableShowingActions"].get_to<bool>( ConfigData_.EnableShowingActions );
		json["RichPresence"]["EnableShowingGuns"].get_to<bool>( ConfigData_.EnableShowingGuns );
		json["RichPresence"]["EnableShowingFirstButton"].get_to<bool>( ConfigData_.EnableShowingFirstButton );
		json["RichPresence"]["EnableShowingSecondButton"].get_to<bool>( ConfigData_.EnableShowingSecondButton );
		json["RichPresence"]["FirstButtonText"].get_to<std::string>( ConfigData_.FirstButtonText );
		json["RichPresence"]["FirstButtonURL"].get_to<std::string>( ConfigData_.FirstButtonURL );
		json["RichPresence"]["SecondButtonText"].get_to<std::string>( ConfigData_.SecondButtonText );
		json["RichPresence"]["SecondButtonURL"].get_to<std::string>( ConfigData_.SecondButtonURL );

		// ServerLogoNames
		json["ServerLogoNames"]["Default"].get_to<std::string>( ConfigData_.Default );
		json["ServerLogoNames"]["ArizonaRP"].get_to<std::string>( ConfigData_.ArizonaRP );
		json["ServerLogoNames"]["SAMPRP"].get_to<std::string>( ConfigData_.SAMPRP );
		json["ServerLogoNames"]["EvolveRP"].get_to<std::string>( ConfigData_.EvolveRP );
		json["ServerLogoNames"]["DiamondRP"].get_to<std::string>( ConfigData_.DiamondRP );
		json["ServerLogoNames"]["AdvanceRP"].get_to<std::string>( ConfigData_.AdvanceRP );
		json["ServerLogoNames"]["TrinityRP"].get_to<std::string>( ConfigData_.TrinityRP );
		json["ServerLogoNames"]["AbsoluteRP"].get_to<std::string>( ConfigData_.AbsoluteRP );
		json["ServerLogoNames"]["HackMySoftware"].get_to<std::string>( ConfigData_.HMS );
		json["ServerLogoNames"]["SR_team"].get_to<std::string>( ConfigData_.SRT );

		// MainActions
		json["MainActionsText"]["DisabledActionsText"].get_to<std::string>( ConfigData_.DisabledActionsText );
		json["MainActionsText"]["DoesNothing"].get_to<std::string>( ConfigData_.DoesNothing );
		json["MainActionsText"]["Running"].get_to<std::string>( ConfigData_.Running );

		// Actions
		json["ActionsText"]["TryingConnection"].get_to<std::string>( ConfigData_.TryingConnection );
		json["ActionsText"]["ShowDialog"].get_to<std::string>( ConfigData_.ShowDialog );
		json["ActionsText"]["ShowGameText"].get_to<std::string>( ConfigData_.ShowGameText );
		json["ActionsText"]["ShowTextDraw"].get_to<std::string>( ConfigData_.ShowTextDraw );
		json["ActionsText"]["Automobile"].get_to<std::string>( ConfigData_.Automobile );
		json["ActionsText"]["MonsterTruck"].get_to<std::string>( ConfigData_.MonsterTruck );
		json["ActionsText"]["Quad"].get_to<std::string>( ConfigData_.Quad );
		json["ActionsText"]["Helicopter"].get_to<std::string>( ConfigData_.Helicopter );
		json["ActionsText"]["Plane"].get_to<std::string>( ConfigData_.Plane );
		json["ActionsText"]["Boat"].get_to<std::string>( ConfigData_.Boat );
		json["ActionsText"]["Train"].get_to<std::string>( ConfigData_.Train );
		json["ActionsText"]["Bike"].get_to<std::string>( ConfigData_.Bike );
		json["ActionsText"]["BMX"].get_to<std::string>( ConfigData_.BMX );

	} catch ( ... ) {
		Save();
	}

	config.close();
}

std::filesystem::path Config::GetConfig() {
	std::filesystem::path modulePath = Utility::GetCurrentModulePath();
	std::filesystem::path path = std::filesystem::current_path();
	std::filesystem::path name = "!DiscordPresence";
	if ( modulePath.has_parent_path() )
		path = modulePath.parent_path();
	if ( modulePath.has_stem() )
		name = modulePath.stem();
	return ( path / ( name.string() + ".json" ) );
}