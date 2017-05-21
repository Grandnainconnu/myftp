/*
** command.c for command in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri May 19 10:49:28 2017 Jean Walrave
** Last update Sun May 21 19:37:36 2017 Jean Walrave
*/

#include <string.h>
#include "my_ftp.h"

static t_command	g_commands[] = {
  {"SYST", &command_syst},
  {"LIST", &command_list},
  {"PWD", &command_pwd},
  {"CWD", &command_cwd},
  {"DELE", &command_dele},
  {"PORT", &command_port},
  {"PASV", &command_pasv},
  {"RETR", &command_retr},
  {"STOR", &command_stor},
  {"TYPE", &command_type},
  {"NOOP", &command_noop},
};

void	treat_command(t_ftp_client *client, char **argv)
{
  int	i;
  int	size;

  i = -1;
  size = sizeof(g_commands) / sizeof(t_command);
  while (++i < size)
    if (argv[0] && !strcmp(argv[0], g_commands[i].command))
      return (g_commands[i].function(client, argv));
  message(client->fd, 502, "Command not implemented.");
}
