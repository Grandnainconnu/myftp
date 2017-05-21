/*
** command_handler.c for command_handler in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Tue May 16 19:40:36 2017 Jean Walrave
** Last update Sun May 21 22:08:30 2017 Jean Walrave
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "my_ftp.h"

const char	*get_input_command(int fd)
{
  char		*command;

  if ((command = get_next_line(fd)) == NULL)
    return (NULL);
  if (command[strlen(command) - 1] == '\r')
    command[strlen(command) - 1] = 0;
  return ((const char *)command);
}

static char	**get_splitted_command(const char *command)
{
  int		n;
  char		*splitter;
  char		**splitted_command;

  n = 0;
  splitter = strtok((char *)command, " ");
  splitted_command = NULL;
  while (splitter)
    {
      if ((splitted_command = \
	   realloc(splitted_command, sizeof(char *) * ++n)) == NULL)
	return (NULL);
      splitted_command[n - 1] = splitter;
      splitter = strtok(NULL, " ");
    }
  splitted_command = realloc(splitted_command, sizeof(char *) * (n + 1));
  splitted_command[n] = 0;
  return (splitted_command);
}

void	handle_client_input(t_ftp_client *client)
{
  char	*command;
  char	**splitted_command;

  while ((command = (char *)get_input_command(client->fd)) != NULL \
	 && strcmp("QUIT", command)
	 && (splitted_command = get_splitted_command(command)) != NULL)
    {
      if (!strcmp("", command))
	continue;
      printf("Client \"%d\" send: \"%s\"\n", client->fd, command);
      if (splitted_command[0] && !strcmp("USER", splitted_command[0]))
	client_auth_login(client, splitted_command[1]);
      else if (splitted_command[0] && !strcmp("PASS", splitted_command[0]))
	client_auth_passwd(client, splitted_command[1]);
      else if (client->is_logged == false)
	message(client->fd, 530, "Permission denied.");
      else
	treat_command(client, splitted_command);
      free(splitted_command);
      free(command);
    }
}
