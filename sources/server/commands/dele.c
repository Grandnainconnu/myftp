/*
** dele.c for dele in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sat May 20 17:14:24 2017 Jean Walrave
** Last update Sat May 20 17:21:56 2017 Jean Walrave
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "my_ftp.h"

void	command_dele(t_ftp_client *client, char **argv)
{
  if (remove(argv[1]) == -1)
    message(client->fd, 550, strerror(errno));
  else
    message(client->fd, 250, "File successfully removed.");
}
