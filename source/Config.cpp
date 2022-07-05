#include "Config.h"
#include <Windows.h>
#include <fstream>
#include "Utility.h"

struct Config::ConfigData ConfigData_;

struct Config::ConfigData* Config::Get() {
	return &ConfigData_;
}

void Config::Save() {
	nlohmann::ordered_json json;

	json["Settings"]["UpdateRate"] = ConfigData_.UpdateRate;

	json["MainActions"]["DoesNothing"] = ConfigData_.DoesNothing;
	json["MainActions"]["Running"] = ConfigData_.Running;

	json["PacketsActions"]["TryingConnection"] = ConfigData_.TryingConnection;

	json["RPCActions"]["ShowDialog"] = ConfigData_.ShowDialog;
	json["RPCActions"]["ShowGameText"] = ConfigData_.ShowGameText;
	json["RPCActions"]["ShowTextDraw"] = ConfigData_.ShowTextDraw;

	json["GTAActions"]["Automobile"] = ConfigData_.Automobile;
	json["GTAActions"]["MonsterTruck"] = ConfigData_.MonsterTruck;
	json["GTAActions"]["Quad"] = ConfigData_.Quad;
	json["GTAActions"]["Helicopter"] = ConfigData_.Helicopter;
	json["GTAActions"]["Plane"] = ConfigData_.Plane;
	json["GTAActions"]["Boat"] = ConfigData_.Boat;
	json["GTAActions"]["Train"] = ConfigData_.Train;
	json["GTAActions"]["Bike"] = ConfigData_.Bike;
	json["GTAActions"]["BMX"] = ConfigData_.BMX;

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

		json["Settings"]["UpdateRate"].get_to<int>( ConfigData_.UpdateRate );

		json["MainActions"]["DoesNothing"].get_to<std::string>( ConfigData_.DoesNothing );
		json["MainActions"]["Running"].get_to<std::string>( ConfigData_.Running );

		json["PacketsActions"]["TryingConnection"].get_to<std::string>( ConfigData_.TryingConnection );

		json["RPCActions"]["ShowDialog"].get_to<std::string>( ConfigData_.ShowDialog );
		json["RPCActions"]["ShowGameText"].get_to<std::string>( ConfigData_.ShowGameText );
		json["RPCActions"]["ShowTextDraw"].get_to<std::string>( ConfigData_.ShowTextDraw );

		json["GTAActions"]["Automobile"].get_to<std::string>( ConfigData_.Automobile );
		json["GTAActions"]["MonsterTruck"].get_to<std::string>(ConfigData_.MonsterTruck);
		json["GTAActions"]["Quad"].get_to<std::string>( ConfigData_.Quad );
		json["GTAActions"]["Helicopter"].get_to<std::string>( ConfigData_.Helicopter );
		json["GTAActions"]["Plane"].get_to<std::string>( ConfigData_.Plane );
		json["GTAActions"]["Boat"].get_to<std::string>( ConfigData_.Boat );
		json["GTAActions"]["Train"].get_to<std::string>( ConfigData_.Train );
		json["GTAActions"]["Bike"].get_to<std::string>( ConfigData_.Bike );
		json["GTAActions"]["BMX"].get_to<std::string>( ConfigData_.BMX );

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