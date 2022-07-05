#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <filesystem>
#include <nlohmann/json.hpp>

class Config
{
public:
	struct ConfigData
	{
		int UpdateRate = 2000;

		std::string DoesNothing = u8"Ничего не делает =)";
		std::string Running = u8"Летает на ногах =)";

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
		std::string Bike = u8"Едет на велосипеде";
		std::string BMX = u8"Едет на БМХ";
	}; // struct ConfigData

	static void Save();
	static void Load();

	static struct ConfigData* Get();
private:
	static std::filesystem::path GetConfig();
}; // class Config

#endif // !_CONFIG_H_