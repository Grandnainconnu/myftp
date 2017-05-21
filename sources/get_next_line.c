/*
** get_next_line.c for get_next_line in /home/jean.walrave/projects/epitech/PSU_2016_myftp
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Sun May 14 23:29:55 2017 Jean Walrave
** Last update Sun May 14 23:29:55 2017 Jean Walrave
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

static t_stack	*add_elem(t_stack *list, char c)
{
  t_stack	*elem;
  t_stack	*tmp;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (NULL);
  elem->value = c;
  elem->next = NULL;
  if (list)
    {
      tmp = list;
      while (tmp->next)
        tmp = tmp->next;
      tmp->next = elem;
      return (list);
    }
  else
    return (elem);
}

static int	is_line(t_stack *list)
{
  t_stack	*tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->value == '\0' || tmp->value == '\n')
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

static int	line_size(t_stack *list)
{
  int		i;
  t_stack	*tmp;

  i = 0;
  tmp = list;
  while (tmp)
    {
      if (tmp->value == '\0' || tmp->value == '\n')
	return (i);
      tmp = tmp->next;
      i++;
    }
  return (i);
}

static char	*to_str(t_stack **list)
{
  int		i;
  t_stack	*tmp;
  char		*str;

  i = 0;
  if (*list == NULL)
    return (NULL);
  if ((str = malloc(sizeof(char) * (line_size(*list) + 1))) == NULL)
    return (NULL);
  while (*list && (*list)->value != '\0' && (*list)->value != '\n')
    {
      tmp = *list;
      str[i++] = (*list)->value;
      *list = (*list)->next;
      free(tmp);
    }
  str[i] = 0;
  if (*list)
    {
      tmp = *list;
      *list = (*list)->next;
      free(tmp);
    }
  return (str);
}

char			*get_next_line(const int fd)
{
  static t_stack	*list = NULL;
  int			i;
  int			rb;
  char			buffer[READ_SIZE];

  if (is_line(list))
    return (to_str(&list));
  i = 0;
  while (i < READ_SIZE)
    buffer[i++] = 0;
  if ((rb = read(fd, buffer, READ_SIZE)) < 0)
    return (NULL);
  if (rb == 0)
    return (to_str(&list));
  i = 0;
  while (i < rb)
    list = add_elem(list, buffer[i++]);
  return (get_next_line(fd));
}
