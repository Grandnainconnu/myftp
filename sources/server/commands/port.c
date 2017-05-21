/*
** port.c for port in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sat May 20 18:34:02 2017 Jean Walrave
** Last update Sun May 21 18:12:22 2017 Jean Walrave
*/

#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "my_ftp.h"

static int		create_data_socket(const char *ip, unsigned int port)
{
  int			data_socket;
  struct sockaddr_in	dss;

  if ((data_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  dss.sin_family = AF_INET;
  dss.sin_addr.s_addr = inet_addr(ip);
  dss.sin_port = htons(port);
  if (connect(data_socket, (struct sockaddr *)&dss, sizeof(dss)) < 0)
    return (-1);
  return (data_socket);
}

void		command_port(t_ftp_client *client, char **argv)
{
  int		ip[4];
  int		port[2];
  char		pip[1024];
  unsigned int	pport;

  if (argv[1] == NULL)
    return ((void)message(client->fd, 550, "Please specify parameters."));
  sscanf(argv[1], "%d,%d,%d,%d,%d,%d", \
	 &ip[0], &ip[1], &ip[2], &ip[3], &port[0], &port[1]);
  memset(pip, 0, sizeof(pip));
  sprintf(pip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  pport = port[0] << 8 | port[1];
  if ((client->dfd = create_data_socket(pip, pport)) == -1)
    return ((void)message(client->fd, 550, "Unable to create data socket."));
  client->is_passive = false;
  message(client->fd, 200, "Data socket created.");
}
