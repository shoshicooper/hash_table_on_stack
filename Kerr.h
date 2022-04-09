#ifndef KeyError_h
#define KeyError_h
#include <iostream>

// (c) 2022 Shoshi (Sharon) Cooper.  No duplication is permitted for commercial use.  Any significant changes made must be
// stated explicitly and the original source code, if used, must be available and credited to Shoshi (Sharon) Cooper.

struct KeyError : public std::exception
{
   std::string s;
   KeyError(std::string ss) : s(ss) {}
   ~KeyError() throw () {}
   const char* what() const throw() { return s.c_str(); }
};

#endif