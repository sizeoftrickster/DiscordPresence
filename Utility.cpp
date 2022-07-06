#include "Utility.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

std::string Utility::cp1251ToUTF8( const char* str ) {
    std::string res;
    int result_u, result_c;
    result_u = MultiByteToWideChar( 1251, 0, str, -1, 0, 0 );
    if ( !result_u ) { 
        return 0; 
    }
    wchar_t* ures = new wchar_t[result_u];
    if ( !MultiByteToWideChar( 1251, 0, str, -1, ures, result_u ) ) {
        delete[] ures;
        return 0;
    }
    result_c = WideCharToMultiByte( 65001, 0, ures, -1, 0, 0, 0, 0 );
    if ( !result_c ) {
        delete[] ures;
        return 0;
    }
    char* cres = new char[result_c];
    if ( !WideCharToMultiByte( 65001, 0, ures, -1, cres, result_c, 0, 0 ) ) {
        delete[] cres;
        return 0;
    }
    delete[] ures;
    res.append( cres );
    delete[] cres;
    return res;
}

std::string Utility::utf8ToCp1251( std::string utf8 ) {
    if (!utf8.empty())
    {
        int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
        if (wchlen > 0 && wchlen != 0xFFFD)
        {
            std::vector<wchar_t> wbuf(wchlen);
            MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
            std::vector<char> buf(wchlen);
            WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);

            return std::string(&buf[0], wchlen);
        }
    }
    return std::string();
}

std::filesystem::path Utility::GetCurrentModulePath() {
    wchar_t lpFilename[MAX_PATH];
    GetModuleFileNameW( reinterpret_cast<HMODULE>( &__ImageBase ), lpFilename, MAX_PATH );
    return lpFilename;
}

HMODULE Utility::GetCurrentModule() {
    return GetModuleHandleA( GetCurrentModulePath().string().data() );
}