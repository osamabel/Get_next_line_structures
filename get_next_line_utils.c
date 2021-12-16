/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:38:41 by obelkhad          #+#    #+#             */
/*   Updated: 2021/12/16 16:29:25 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

void	ft_lstadd_bask(t_list **lst, t_list *new)
{
	t_list *head;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			head = (*lst);
			while (head->next)
				head = head->next;
			head->next = new;
		}
	}
}

t_list	*ft_lstnew(char *buf, int check)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->buffer = malloc(sizeof(char) * (check + 1));
	strncpy(node->buffer, buf, check + 1);
	node->next = NULL;
	return (node);
}

void	creat_line(t_list **lst, char **line)
{
	size_t	i;
	size_t	check;
	size_t	totale;
	t_list	*node;

	node = *lst;
	i = 0;
	totale = 0;
	check = 0;


	while (node)
	{
		totale += strlen((node)->buffer);
		(node) = (node)->next;
	}
	node = *lst;

	*line = malloc(sizeof(char) * (totale+ 1));

	while (node)
	{
		i += check;
		check = check_end_of_line(node->buffer);
		strncpy(*line + i, node->buffer, check + 1);
		node = node->next;
	}
	*(*line + totale) = '\0';
	ft_lstclear(lst);
}

void	ft_strjoin(char **line, char *lost_chars)
{
	size_t		index;
	char		*result;

	index = 0;
	result = *line;
	*line = malloc(sizeof(char) * (strlen(result) + strlen(lost_chars) + 1));
	strncpy(*line + index, lost_chars, strlen(lost_chars));
	index += strlen(lost_chars);
	strncpy(*line + index, result, strlen(result));
	index += strlen(result);
	free(result);
	*(*line + index) = '\0';
}

char	*ft_lst_to_string(t_list **lst, char **buf, size_t index)
{
	static char	*lost_chars;
	char		*line;
	size_t 		i;
	size_t 		j;

	i = 0;
	j = index;
	line = NULL;
	while (j++ < BUFFER_SIZE - 1)
		i++;
	creat_line(lst, &line);
	if (lost_chars)
	{
		ft_strjoin(&line, lost_chars);
		free(lost_chars);
	}
	if (i > 0)
	{
		lost_chars = malloc(sizeof(char) * (i + 1));
		strncpy(lost_chars, *buf + index + 1, BUFFER_SIZE + 1 - index);
	}
	free(*buf);
	*buf = NULL;
	return (line);
}
