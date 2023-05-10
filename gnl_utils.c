/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:50:31 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 11:00:10 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	remove_list(t_gnl **head, int fd)
{
	t_gnl	*tmp;
	t_gnl	*before;

	tmp = *head;
	if (tmp->fd == fd)
	{
		*head = (*head)->next;
		free(tmp);
	}
	else
	{
		while (tmp)
		{
			if (tmp->fd == fd)
				break ;
			before = tmp;
			tmp = tmp->next;
		}
		before->next = tmp->next;
		free(tmp);
	}
}

char	*ft_free(t_gnl **list, char **s1, char *s2, int fd)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (list)
		remove_list(list, fd);
	if (s2)
		free(s2);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2, size_t s1_len, size_t s2_len)
{
	char	*tmp;
	size_t	i;

	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	tmp = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!tmp)
	{
		free(s1);
		return (0);
	}
	i = -1;
	while (++i < s1_len)
		tmp[i] = s1[i];
	i--;
	while (++i < s1_len + s2_len)
		tmp[i] = s2[i - s1_len];
	tmp[i] = '\0';
	free(s1);
	s1 = NULL;
	return (tmp);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *) &s[i]);
	else
		return (0);
}
