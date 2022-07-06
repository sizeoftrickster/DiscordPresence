#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <filesystem>

class Utility
{
public:
	static std::string cp1251ToUTF8( const char* str );
	static std::string utf8ToCp1251( std::string str );

	static std::filesystem::path GetCurrentModulePath();
	static HMODULE GetCurrentModule();
};

#endif // !_UTILITY_H_