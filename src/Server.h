#include <iostream>

class Server_t
{
private:
    int port;

public:
    Server_t(int port);
    ~Server_t();

    int initServer();
};