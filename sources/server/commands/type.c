/*
** type.c for type in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sun May 21 19:40:44 2017 Jean Walrave
** Last update Sun May 21 19:41:06 2017 Jean Walrave
*/

#include "my_ftp.h"

void	command_type(t_ftp_client *client, char **argv __attribute__((unused)))
{
  message(client->fd, 200, "Type ok.");
}
