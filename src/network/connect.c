#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <config.h>
#include <network/connect.h>
#include <network/server_info.h>

void connect_server(const char *server_address, uint16_t server_port)
{
  struct sockaddr_in servaddr;
  struct irc_server_info *server_info = config_get_server_info();
  int sockfd;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    /* TODO: Proper error handling and exit */
    perror("failed to create socket");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(server_address);
  servaddr.sin_port = htons(server_port);

  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    /* TODO: Proper error handling and exit */
    fprintf(stderr, "couldn't connect to '%s': ", server_address);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  server_info->address = strdup(server_address);
  server_info->port = server_port;
  server_info->sockfd = sockfd;
  server_info->is_connected = true;
}

void close_server_connection(void)
{
  struct irc_server_info *server_info = config_get_server_info();
  if (server_info->is_connected) {
    close(server_info->connfd);
    server_info->is_connected = false;
  }

  if (server_info->address) {
    free(server_info->address);
    server_info->address = NULL;
  }
}