/*
** get_next_line.h for get_next_line in /home/jean.walrave/projects/epitech/PSU_2016_myftp
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sun May 14 23:09:51 2017 Jean Walrave
** Last update Sun May 14 23:10:05 2017 Jean Walrave
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_
# ifndef READ_SIZE
#  define READ_SIZE 1024
# endif

typedef struct		s_stack
{
  char			value;
  struct s_stack	*next;
}			t_stack;

char	*get_next_line(const int);

#endif /* !GET_NEXT_LINE_H_ */
