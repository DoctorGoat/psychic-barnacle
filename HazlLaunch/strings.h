// typedef const void* LPCVOID;
// this points to anything? i'm not sure why this is even defined. just use void*

//_EXPORT_STD using string = basic_string<char, char_traits<char>, allocator<char>>;
// lpcstr:  typedef char* PSTR, *LPSTR; 
// A 32-bit pointer to a string of 8-bit characters, which MAY be null-terminated.
// lpstr: this is lpcstr

// A LMSTR is a 32-bit pointer to a null-terminated string of 16-bit Unicode characters.
// typedef WCHAR* LMSTR; 
//_EXPORT_STD using wstring = basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t>>;
// typedef const wchar_t* LPCWSTR; 
// An LPCWSTR is a 32-bit pointer to a constant string of 16-bit Unicode characters, which MAY be null-terminated.
// 

//_EXPORT_STD using u16string = basic_string<char16_t, char_traits<char16_t>, allocator<char16_t>>;
// typedef wchar_t* LPWSTR, *PWSTR;
// The LPWSTR type is a 32-bit pointer to a string of 16-bit Unicode characters, which MAY be null-terminated.
// why are these separate??
// typedef const wchar_t* LMCSTR;
// A LMCSTR is a 32-bit pointer to a constant null-terminated string of 16-bit Unicode characters.
// 
// 
//_EXPORT_STD using u32string = basic_string<char32_t, char_traits<char32_t>, allocator<char32_t>>;
//This is the Hazl library general reference material for strings because C people are deranged
//and reinvent the wheel so often that it boggles the mind


