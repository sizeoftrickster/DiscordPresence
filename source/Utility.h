#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <filesystem>

class Utility
{
public:
	static std::string Win1251ToUTF8( std::string string );

	static std::filesystem::path GetCurrentModulePath();
	static HMODULE GetCurrentModule();
private:
	static void Win1251ToUTF1( char* out, const char* in );
};

#endif // !_UTILITY_H_