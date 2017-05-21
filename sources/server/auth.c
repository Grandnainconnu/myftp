/*
** auth.c for auth in /home/jean.walrave/projects/epitech/PSU_2016_myftp/sources/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sun May 14 17:23:00 2017 Jean Walrave
** Last update Fri May 19 16:01:50 2017 Jean Walrave
*/

#include <stdlib.h>
#include <string.h>
#include "my_ftp.h"

void	client_auth_login(t_ftp_client *client, char *login)
{
  if (client->is_logged == true)
    message(client->fd, 530, "Can't change user.");
  else if (login)
    {
      client->user = strdup(login);
      message(client->fd, 331, "User name okay, need password.");
    }
  else
    message(client->fd, 332, "A login is required.");
}

void	client_auth_passwd(t_ftp_client *client, char *passwd)
{
  if (client->is_logged == true)
    message(client->fd, 230, "Already logged in.");
  else if (client->user == NULL)
    message(client->fd, 332, "A login is required.");
  else if ((!strcmp("Anonymous", client->user)
	    || !(strcmp("anonymous", client->user)))
	   && passwd == NULL)
    {
      free(client->user);
      client->user = NULL;
      client->is_logged = true;
      message(client->fd, 230, "User logged in, proceed.");
    }
  else
    message(client->fd, 331, "Wrong password.");
}
