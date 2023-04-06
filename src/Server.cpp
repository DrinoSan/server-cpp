#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

// Porject Headers
#include "Server.h"
#include "utils/logging.h"

//---------------------------------------------------------------------
Server_t::Server_t(int port) : port{port}
{
    std::cout << "------------ BEGIN Init SERVER ------------\n";
    std::cout << "PORT: " << port << '\n';
    std::cout << "------------ END Init SERVER --------------\n";
}

//---------------------------------------------------------------------
Server_t::~Server_t()
{
}

//---------------------------------------------------------------------
int Server_t::initServer()
{
    int fd;
    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        traceError("Failed to create Socket FD");
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
    {
        traceError("Failed setsockopt");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port);
    addr.sin_addr.s_addr = ntohl(0);

    int rv;
    if ((rv = bind(fd, (const sockaddr *)&addr, sizeof(addr))))
    {
        traceError("Failed binding to socket!");
    }

    if ((rv = listen(fd, 5)))
    {
        traceError("Failed listening");
    }

    // Waiting for client
    // sockaddr_storage needed if i want to print from whom i got a connection
    struct sockaddr_in client_addr = {};
    socklen_t socklen = sizeof(client_addr);

    while (true)
    {
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &socklen);
        if (connfd < 0)
        {
            traceError("accept() error");
            return -1;
        }

        char rbuf[100];
        read(connfd, rbuf, sizeof(rbuf));
        traceNotice(rbuf);

        const char wbuf[19] = "Hello from Server!";
        write(connfd, wbuf, sizeof(wbuf));
        memset(rbuf, '\0', sizeof(rbuf));
        read(connfd, rbuf, sizeof(rbuf));
        traceNotice(rbuf);
        close(connfd);
    }
}