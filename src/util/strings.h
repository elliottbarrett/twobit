#ifndef TB_STRINGS_H_INCLUDED
#define TB_STRINGS_H_INCLUDED

#include <string>
#include <string.h>

inline bool starts_with(std::string s, std::string prefix)
{
    return strncmp(s.c_str(), prefix.c_str(), prefix.size()) == 0;
}

#endif