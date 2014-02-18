/******************************************************************************* 
 *  @file      EncodeAndDecode.cpp 2013\4\25 15:20:32 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "Misc/EncodeAndDecode.h"

#include <string>
#if defined(CPS_OS_WINDOWS)
    #include <Windows.h>
#endif

#include "boost/scoped_array.hpp"

/******************************************************************************/

CPS_MISC_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
// public
std::string utf8urlEncode( const char* s )
{
    std::string resultURLStr;
    static const char hex[] = "0123456789abcdef";

    for (; *s; ++s)
    {
        const char c = *s;
        switch (c)
        {
        case '&':
        case '?':
        case '#':
        case '%':
        case '+':
        case '=':
        case '\'':
        case '/':
        case '"':
        case '@':
        case '$':
        case ',':
        case ':':
        case ';':
        case '<':
        case '>':
        case '{':
        case '}':
        case '|':
        case '\\':
        case '^':
        case '~':
        case '[':
        case ']':
        case '`':
            resultURLStr.append(1, '%');
            resultURLStr.append(1, hex[(c & 0xf0) >> 4]);
            resultURLStr.append(1, hex[c & 0x0f]);
            break;
        case ' ':
            resultURLStr.append(1, '+');
            break;
        default:
            resultURLStr.append(1, c);
        }
    }

    return resultURLStr;
}

#if defined(CPS_OS_WINDOWS)

std::string& UCS2ToUTF8(OUT std::string& destStr, IN const wchar_t*src, IN size_t size)
{
    assert(destStr.empty());
    int cch2 = ::WideCharToMultiByte(CP_UTF8, 0, src, size, 0, 0, 0, 0);
    boost::scoped_array<char> str2(new char[cch2 + 1]);
    ::WideCharToMultiByte(CP_UTF8, 0, src, size, str2.get(), cch2 + 1, 0, 0);
    str2[cch2] = '\0';
    destStr = str2.get();
    return destStr;
}

std::wstring& UTF8ToUCS2(OUT std::wstring& destStr, IN const char*src, IN size_t size)
{

    assert(destStr.empty());
    int cch2 = ::MultiByteToWideChar(CP_UTF8, 0, src, size, NULL, 0);
    boost::scoped_array<wchar_t> str2(new wchar_t[cch2 + 1]);
    ::MultiByteToWideChar(CP_UTF8, 0, src, size, str2.get(), cch2);
    str2[cch2] = L'\0';
    destStr = str2.get();
    return destStr;
}


std::string& UCS2ToGBK(OUT std::string& destStr, IN const wchar_t*src, IN size_t size)
{
    assert(destStr.empty());
    int cch2 = ::WideCharToMultiByte(CP_ACP, 0, src, size, 0, 0, 0, 0);
    boost::scoped_array<char> str2(new char[cch2 + 1]);
    ::WideCharToMultiByte(CP_ACP, 0, src, size, str2.get(), cch2 + 1, 0, 0);
    str2[cch2] = '\0';
    destStr = str2.get();
    return destStr;
}

std::wstring& GBKToUCS2(OUT std::wstring& destStr, IN const char*src, IN size_t size)
{
    int cch2 = ::MultiByteToWideChar(CP_ACP, 0, src, size, NULL, 0);
    boost::scoped_array<wchar_t> str2(new wchar_t[cch2 + 1]);
    ::MultiByteToWideChar(CP_ACP, 0, src, size, str2.get(), cch2);
    str2[cch2] = L'\0';
    destStr = str2.get();
    return destStr;
}

std::string& GBKToUTF8(OUT std::string& destStr, IN const char*src, IN size_t size)
{
    std::wstring tempStr;
    GBKToUCS2(tempStr, src, size);
    return UCS2ToUTF8(destStr, tempStr.c_str(), tempStr.size());
}

std::string& UTF8ToGBK(OUT std::string& destStr, IN const char*src, IN size_t size)
{
    std::wstring tempStr;
    UTF8ToUCS2(tempStr, src, size);
    return UCS2ToGBK(destStr, tempStr.c_str(), tempStr.size());
}

#endif

CPS_MISC_NAMESPACE_END
// 
// -----------------------------------------------------------------------------

