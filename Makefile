##
## Makefile for Makefile in /home/jean.walrave/projects/epitech/PSU_2016_nmobjdump
## 
## Made by Jean Walrave
## Login   <jean.walrave@epitech.net>
## 
## Started on  Sat Feb 18 10:00:32 2017 Jean Walrave
## Last update Sun May 21 20:06:05 2017 Jean Walrave
##

SERVER_SRCS	= sources/server/server.c \
		  sources/server/socket.c \
		  sources/server/handler.c \
		  sources/server/auth.c \
		  sources/server/commands/command.c \
	          sources/server/commands/syst.c \
	          sources/server/commands/list.c \
	          sources/server/commands/pwd.c \
	          sources/server/commands/cwd.c \
	          sources/server/commands/dele.c \
	          sources/server/commands/port.c \
	          sources/server/commands/pasv.c \
	          sources/server/commands/stor.c \
	          sources/server/commands/retr.c \
	          sources/server/commands/type.c \
	          sources/server/commands/noop.c \
		  sources/get_next_line.c

CLIENT_SRCS	= sources/client/client.c

SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)

CFLAGS		= -W -Wextra -Wall -Werror -I./includes/

CC		= gcc

RM		= rm -rf

SERVER_NAME	= server

CLIENT_NAME	= client

all:		$(SERVER_NAME) $(CLIENT_NAME)
		@echo        "|-----------------------|"
		@echo        "|     IT\'S WORKING!    |"
		@echo        "|     ____v__   _  _    |"
		@echo        "|    | 0     |  \||/    |"
		@echo        "|    |       |__/ |     |"
		@echo        "|    ~~~~~~~~~~~~~~~    |"
		@echo        "|-----------------------|"

$(SERVER_NAME): $(SERVER_OBJS)
		$(CC) -o $(SERVER_NAME) $(SERVER_OBJS)

$(CLIENT_NAME): $(CLIENT_OBJS)
		$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS)

clean:
		$(RM) $(SERVER_OBJS)
		$(RM) $(CLIENT_OBJS)

fclean:		clean
		$(RM) $(SERVER_NAME)
		$(RM) $(CLIENT_NAME)

re:		fclean all

.PHONY:		all clean fclean re
