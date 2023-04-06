#include <iostream>
#include <string>

//---------------------------------------------------------------------
inline void err(std::string msg)
{
    std::cerr << "[ERROR] " << msg << '\n';
}

//---------------------------------------------------------------------
inline void msg(std::string msg)
{
    std::cerr << "[NOTICE] " << msg << '\n';
}