#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

// Porject Headers
#include "Server.h"
#include "utils/logging.h"

constexpr int CHUNK_SIZE = 10;

//---------------------------------------------------------------------
Server_t::Server_t(int port) : port{port} {
  std::cout << "------------ BEGIN Init SERVER ------------\n";
  std::cout << "PORT: " << port << '\n';
  std::cout << "------------ END Init SERVER --------------\n";
}

//---------------------------------------------------------------------
Server_t::~Server_t() {}

//---------------------------------------------------------------------
void Server_t::set_non_blocking(int fd) {
  errno = 0;
  int flags = fcntl(fd, F_GETFL, 0);
  if (errno) {
    traceError("fcntl error");
    return;
  }

  flags |= O_NONBLOCK;

  errno = 0;
  (void)fcntl(fd, F_SETFL, flags);
  if (errno) {
    traceError("fcntl error");
  }
}

//---------------------------------------------------------------------
int Server_t::initServer() {
  int fd;
  if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    traceError("Failed to create Socket FD");
  }

  int opt = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
    traceError("Failed setsockopt");
  }

  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = ntohs(port);
  addr.sin_addr.s_addr = ntohl(0);

  int rv;
  if ((rv = bind(fd, (const sockaddr *)&addr, sizeof(addr)))) {
    traceError("Failed binding to socket!");
  }

  if ((rv = listen(fd, 5))) {
    traceError("Failed listening");
  }

  // Waiting for client
  // sockaddr_storage needed if i want to print from whom i got a connection
  struct sockaddr_in client_addr = {};
  socklen_t socklen = sizeof(client_addr);

  while (true) {
    int connfd = accept(fd, (struct sockaddr *)&client_addr, &socklen);
    if (connfd < 0) {
      traceError("accept() error");
      return -1;
    }

    set_non_blocking(connfd);

    char rbuf[1000];
    readAll(connfd, rbuf, sizeof(rbuf));
    traceNotice(rbuf);

    const char wbuf[19] = "Hello from Server!";
    write(connfd, wbuf, sizeof(wbuf));
    memset(rbuf, '\0', sizeof(rbuf));
    sleep(5);
    readAll(connfd, rbuf, sizeof(rbuf));
    traceNotice(rbuf);
    close(connfd);
  }
}

//---------------------------------------------------------------------
int Server_t::readAll(int connfd, char *rbuf, int len) {
  memset(rbuf, 0, len);
  ssize_t rv;
  int bytesRead;
  while (len > 0) {
    rv = read(connfd, rbuf, CHUNK_SIZE);
    if (rv <= 0) {
      return -1;
    }
    len -= (size_t)rv;
    rbuf += rv;
    bytesRead += rv;
  }

  if (rv < 0) {
    return bytesRead;
  }

  traceNotice("READ RV: " + std::to_string(rv));
  return -1;
}