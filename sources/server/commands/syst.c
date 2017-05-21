/*
** syst.c for syst in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server/commands
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri May 19 10:38:02 2017 Jean Walrave
** Last update Sat May 20 19:11:24 2017 Jean Walrave
*/

#include "my_ftp.h"

void	command_syst(t_ftp_client *client, char **argv __attribute__((unused)))
{
  message(client->fd, 215, "UNIX Type: L8.");
}
