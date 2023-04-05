#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Project Headers
#include "utils/logging.h"
#include "src/Server.h"

int main()
{
    Server_t server{8000};

    server.initServer();

    return 0;
}