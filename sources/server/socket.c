/*
** socket.c for socket in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri May 12 15:31:33 2017 Jean Walrave
** Last update Sun May 21 16:32:54 2017 Jean Walrave
*/

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include "my_ftp.h"

static t_ftp_client	*create_client(int fd, unsigned int ip_cli)
{
  t_ftp_client		*client;

  if ((client = malloc(sizeof(t_ftp_client))) == NULL)
    return (fprintf(stderr, "[-] Can't treat client\n"), NULL);
  client->ip = ip_cli;
  client->user = NULL;
  client->passwd = NULL;
  client->is_logged = false;
  client->is_passive = false;
  client->fd = fd;
  client->dfd = -1;
  return (client);
}

static void		delete_client(t_ftp_client *client)
{
  free(client->user);
  free(client->passwd);
  free(client);
}

static void		handle_client(int sock_cli, unsigned int ip_cli)
{
  t_ftp_client	*client;

  printf("[+] Connection accepted\n");
  message(sock_cli, 220, "Hello.");
  if ((client = create_client(sock_cli, ip_cli)) == NULL)
    return;
  handle_client_input(client);
  delete_client(client);
  message(sock_cli, 221, "Goodbye.");
  printf("[-] Connection ended\n");
}

void			socket_server_listen(int sock_srv)
{
  int                   socket_size;
  int                   client_socket;
  struct sockaddr_in    client;

  listen(sock_srv, MAX_SOCKET_QUEUE);
  printf("[+] Waiting for incoming connections...\n");
  while (true)
    {
      socket_size = sizeof(client);
      if ((client_socket = accept(sock_srv, (struct sockaddr *)&client,\
                                  (socklen_t *)&socket_size)) < 0)
        {
          fprintf(stderr, "[-] Connection failed\n");
          return;
        }
      if (!fork())
	{
	  close(sock_srv);
	  handle_client(client_socket, client.sin_addr.s_addr);
	  exit(EXIT_SUCCESS);
        }
      else
	close(client_socket);
    }
}

int			create_socket_server(unsigned int port)
{
  int                   sock_srv;
  struct sockaddr_in    server;
  struct protoent	*tcp_protocol;

  if ((tcp_protocol = getprotobyname("TCP")) == NULL)
    return (fprintf(stderr, "[-] Get TCP protocol failed"), -1);
  if ((sock_srv = socket(AF_INET, SOCK_STREAM, tcp_protocol->p_proto)) == -1)
    return (fprintf(stderr, "[-] Could not create socket\n"), -1);
  if (setsockopt(sock_srv, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    return (fprintf(stderr, "[-] Could not set SO_REUSEADDR\n"), -1);
  printf("[+] Socket created\n");
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);
  if (bind(sock_srv, (struct sockaddr *)&server, sizeof(server)) < 0)
    return (fprintf(stderr, "[-] Bind failed\n"), -1);
  printf("[+] Bind done\n");
  return (sock_srv);
}
