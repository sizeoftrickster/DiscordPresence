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

		std::string DoesNothing = u8"������ �� ������ =)";
		std::string Running = u8"������ �� ����� =)";

		std::string TryingConnection = u8"������������ � �������";

		std::string ShowDialog = u8"������������� ������";
		std::string ShowGameText = u8"������������� ������� �����";
		std::string ShowTextDraw = u8"������������� ���������";

		std::string Automobile = u8"���� � ����������";
		std::string MonsterTruck = u8"���� � �����������";
		std::string Quad = u8"���� �� �����������";
		std::string Helicopter = u8"����� � ��������";
		std::string Plane = u8"����� � ��������";
		std::string Boat = u8"����� �� �����";
		std::string Train = u8"���� �� ������";
		std::string Bike = u8"���� �� ����������";
		std::string BMX = u8"���� �� ���";
	}; // struct ConfigData

	static void Save();
	static void Load();

	static struct ConfigData* Get();
private:
	static std::filesystem::path GetConfig();
}; // class Config

#endif // !_CONFIG_H_