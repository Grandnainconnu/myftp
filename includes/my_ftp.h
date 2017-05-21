/*
** my_ftp.h for my_ftp in /home/jean.walrave/projects/epitech/PSU_2016_myftp
1;4402;0c** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri May 12 15:22:48 2017 Jean Walrave
** Last update Sun May 21 19:38:27 2017 Jean Walrave
*/

#ifndef MY_FTP_H_
# define MY_FTP_H_
# define MAX_SOCKET_QUEUE 10

# include <stdio.h>
# include <stdbool.h>

typedef struct		s_ftp_client
{
  unsigned int		ip;
  char			*user;
  char			*passwd;
  bool			is_logged;
  bool			is_passive;
  int			fd;
  int			dfd;
  struct sockaddr_in	*client_socket;
}			t_ftp_client;

typedef struct		s_command
{
  char			*command;
  void			(*function)(t_ftp_client *, char **);
}			t_command;

/*
** Server
*/
int			message(int, int, const char *);

/*
** Authentification
*/
void			client_auth_login(t_ftp_client *, char *);
void			client_auth_passwd(t_ftp_client *, char *);

/*
** Socket
 */
int			create_socket_server(unsigned int);
void			socket_server_listen(int);

/*
** Handler
*/
void			handle_client_input(t_ftp_client *);
const char		*get_input_command(int);

/*
** Command
*/
void	treat_command(t_ftp_client *, char **);
void	command_syst(t_ftp_client *, char **);
void	command_list(t_ftp_client *, char **);
void	command_pwd(t_ftp_client *, char **);
void	command_cwd(t_ftp_client *, char **);
void	command_dele(t_ftp_client *, char **);
void	command_port(t_ftp_client *, char **);
void	command_pasv(t_ftp_client *, char **);
void	command_retr(t_ftp_client *, char **);
void	command_stor(t_ftp_client *, char **);
void	command_type(t_ftp_client *, char **);
void	command_noop(t_ftp_client *, char **);

#endif /* !MY_FTP_H_ */
