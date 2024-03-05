#include <string>
#include <iostream>
#include <Windows.h>
namespace hazl {
    class strings {
    public:
        //reads a string put in by a normal person and returns a wchar_t
        //struct. conveniently, thos covers LPCWSTR and its variant. h
        static const wchar_t* returnwchar_t(const char* strin)
        {
            size_t newsize = strlen(strin) + 1;
            wchar_t* wcstring = new wchar_t[newsize];
            size_t convertedChars = 0;
            mbstowcs_s(&convertedChars, wcstring, newsize, strin, _TRUNCATE);
            return wcstring;
        }
        static const wchar_t* return16_t(const char* strin)
        {
            size_t newsize = strlen(strin) + 1;
    //        char16_t* wcstring = new char16_t[newsize];
  //          size_t convertedChars = 0;
//            return wcstring;
        };

	private:
		void no() {

		};
	};
}