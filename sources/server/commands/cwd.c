/*
** cwd.c for cwd in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sat May 20 16:56:55 2017 Jean Walrave
** Last update Sat May 20 17:20:35 2017 Jean Walrave
*/

#include <unistd.h>
#include "my_ftp.h"

void	command_cwd(t_ftp_client *client, char **argv)
{
  if (chdir(argv[1]) == -1)
    message(client->fd, 550, "Failed to change directory.");
  else
    message(client->fd, 250, "Directory successfully changed.");
}
