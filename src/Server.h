#include <iostream>

class Server_t {
private:
  int port;

public:
  Server_t(int port);
  ~Server_t();

  int initServer();
  int readAll(int connfd, char *rbuf, int len);
  void set_non_blocking(int fd);
};