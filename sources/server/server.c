/*
** server.c for server in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sun May 21 18:06:41 2017 Jean Walrave
** Last update Sun May 21 18:06:42 2017 Jean Walrave
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "my_ftp.h"

static void		usage(const char *binary)
{
  printf("Usage: %s: port path\n", binary);
}

static int		extract_port(const char *port)
{
  int			ext_port;
  char			*ext_str;

  ext_port = (int)strtol(port, &ext_str, 10);
  if (ext_port > 65535 || port == ext_str)
    return (-1);
  return (ext_port);
}

int	message(int fd, int code, const char *message)
{
  if (code < 0)
    return (dprintf(fd, "%s\n", message));
  return (dprintf(fd, "%d %s\r\n", code, message));
}

int	main(int argc, char **argv)
{
  int	socket_server;
  int	port;
  char	*path;

  if (argc == 1 || argc < 3 || (port = extract_port(argv[1])) == -1)
    return (usage(argv[0]), -1);
  if ((path = argv[2]) && chdir(path) == -1)
    return (perror(path), -1);
  if ((socket_server = create_socket_server((unsigned int)port)) == -1)
    return (-1);
  socket_server_listen(socket_server);
  return (0);
}
