#include <iostream>
#include <string>

//---------------------------------------------------------------------
inline void traceError(std::string msg)
{
    std::cerr << "[ERROR] " << msg << '\n';
}

//---------------------------------------------------------------------
inline void traceNotice(std::string msg)
{
    std::cerr << "[NOTICE] " << msg << '\n';
}