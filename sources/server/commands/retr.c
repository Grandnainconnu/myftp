/*
** retr.c for retr in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sat May 20 18:34:33 2017 Jean Walrave
** Last update Sun May 21 19:51:52 2017 Jean Walrave
*/

#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "my_ftp.h"

static int		send_file(t_ftp_client *client, FILE *file)
{
  int			rd;
  char			buff[READ_SIZE];
  socklen_t		psas;
  struct sockaddr_in	psa;

  psas = sizeof(psa);
  if ((client->is_passive &&
       (client->dfd = accept(client->dfd, (struct sockaddr *)&psa, &psas)) < 0))
    return (message(client->fd, 550, "Unable to perform socket."), -1);
  rd = READ_SIZE;
  memset(buff, 0, sizeof(buff));
  while (rd == READ_SIZE)
    {
      rd = fread(buff, sizeof(char), READ_SIZE - 1, file);
      dprintf(client->dfd, "%s", buff);
      memset(buff, 0, sizeof(buff));
    }
  return (0);
}

void			command_retr(t_ftp_client *client, char **argv)
{
  FILE			*file;

  if (client->dfd < 0)
    return ((void)message(client->fd, 425, "Use PORT or PASV first."));
  if (argv[1] == NULL || !(file = fopen(argv[1], "rb")))
    {
      close(client->dfd);
      return ((void)message(client->fd, 550, "Unable to get file."));
    }
  message(client->fd, 150, "File available, openning...");
  if (send_file(client, file) == -1)
    return;
  message(client->fd, 226, "File getted successfully.");
  fclose(file);
  close(client->dfd);
}
