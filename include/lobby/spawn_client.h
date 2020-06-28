#ifndef TRTS_SPAWN_CLIENT_H
#define TRTS_SPAWN_CLIENT_H
#include <utility>
#include <netinet/in.h>

int SpawnAndConnectGameClient(sockaddr_in address);
int SpawnGameClient(int fd);

#endif
