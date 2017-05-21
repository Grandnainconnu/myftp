/*
** list.c for list in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri May 19 10:57:14 2017 Jean Walrave
** Last update Sun May 21 18:37:26 2017 Jean Walrave
*/

#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include "get_next_line.h"
#include "my_ftp.h"

static int              send_list(t_ftp_client *client, FILE *ls)
{
  char                  buff[READ_SIZE];
  socklen_t             psas;
  struct sockaddr_in    psa;

  psas = sizeof(psa);
  if ((client->is_passive &&
       (client->dfd = accept(client->dfd, (struct sockaddr *)&psa, &psas)) < 0))
    return (message(client->fd, 550, "Unable to perform socket."), -1);
  while (!feof(ls) && fgets(buff, READ_SIZE, ls) != NULL)
    {
      dprintf(client->dfd, "%s", buff);
      memset(buff, 0, READ_SIZE);
    }
  return (0);
}

void	command_list(t_ftp_client *client, char **argv __attribute__((unused)))
{
  FILE	*ls;

  if (client->dfd < 0)
    return ((void)message(client->fd, 425, "Use PORT or PASV first."));
  if (!(ls = popen("ls -la", "r")))
    {
      close(client->dfd);
      return ((void)message(client->fd, 450, "Unable to list files."));
    }
  message(client->fd, 150, "Preparing to list files...");
  if (send_list(client, ls) == -1)
    return;
  message(client->fd, 226, "Successfully list files.");
  pclose(ls);
  close(client->dfd);
}
