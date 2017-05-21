/*
** pasv.c for pasv in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sat May 20 18:34:13 2017 Jean Walrave
** Last update Sun May 21 18:12:34 2017 Jean Walrave
*/

#include <stdio.h>
#include <arpa/inet.h>
#include "my_ftp.h"

static int		create_passive_socket(unsigned int ip)
{
  int			passive_socket;
  struct sockaddr_in	sps;

  if ((passive_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  sps.sin_family = AF_INET;
  sps.sin_addr.s_addr = ip;
  sps.sin_port = 0;
  if (bind(passive_socket, (struct sockaddr *)&sps, sizeof(sps)) == -1 ||
      listen(passive_socket, MAX_SOCKET_QUEUE) == -1)
    return (-1);
  return (passive_socket);
}

void			command_pasv(t_ftp_client *client, \
				     char **argv __attribute__((unused)))
{
  char			msg[1024];
  struct in_addr	ip_addr;

  if ((client->dfd = create_passive_socket(client->ip)) == -1)
    return ((void)message(client->fd, 550, "Unable to enter in passive mode."));
  ip_addr.s_addr = client->ip;
  sprintf(msg, "Entering passive mode (%s).", inet_ntoa(ip_addr));
  client->is_passive = true;
  message(client->fd, 227, msg);
}
