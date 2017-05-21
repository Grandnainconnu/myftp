/*
** stor.c for stor in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sat May 20 18:34:51 2017 Jean Walrave
** Last update Sun May 21 20:06:22 2017 Jean Walrave
*/

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my_ftp.h"

static int		put_file(t_ftp_client *client, FILE *file)
{
  char			*buff;
  socklen_t		psas;
  struct sockaddr_in	psa;

  psas = sizeof(psa);
  if ((client->is_passive &&
       (client->dfd = accept(client->dfd, (struct sockaddr *)&psa, &psas)) < 0))
    return (message(client->fd, 550, "Unable to perform socket."), -1);
  while ((buff = get_next_line(client->dfd)) != NULL)
    {
      fwrite(buff, sizeof(char), strlen(buff), file);
      free(buff);
    }
  return (0);
}

void	command_stor(t_ftp_client *client, char **argv)
{
  FILE	*file;

  if (client->dfd < 0)
    return ((void)message(client->fd, 425, "Use PORT or PASV first."));
  if (argv[1] == NULL || !(file = fopen(argv[1], "wb")))
    {
      close(client->dfd);
      return ((void)message(client->fd, 550, "Unable to create/get file."));
    }
  message(client->fd, 150, "File available, openning...");
  if (put_file(client, file) == -1)
    return;
  message(client->fd, 226, "File putted successfully.");
  fclose(file);
  close(client->dfd);
}
