/*
** noop.c for noop in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sun May 21 19:39:08 2017 Jean Walrave
** Last update Sun May 21 19:40:08 2017 Jean Walrave
*/

#include "my_ftp.h"

void	command_noop(t_ftp_client *client, char **argv __attribute__((unused)))
{
  message(client->fd, 200, "I'm alive.");
}
