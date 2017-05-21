/*
** pwd.c for pwd in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri May 19 11:21:06 2017 Jean Walrave
** Last update Sat May 20 19:11:40 2017 Jean Walrave
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_ftp.h"

void	command_pwd(t_ftp_client *client, char **argv __attribute__((unused)))
{
  char	*cwd;

  if (!(cwd = getcwd(0, 0)))
    return ((void)message(client->fd, 450, "Failed to get PWD."));
  message(client->fd, 257, cwd);
  free(cwd);
}
