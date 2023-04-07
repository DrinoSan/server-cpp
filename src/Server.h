// System Headers
#include <iostream>
#include <netinet/in.h>

class Server_t {
private:
  int port;

public:
  Server_t(int port);
  ~Server_t();

  int initServer();
  int readAll(int connfd, char *rbuf, int len);
  void set_non_blocking(int fd);
  void getClientIP(struct sockaddr_storage addr);
};