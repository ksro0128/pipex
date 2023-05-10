/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:44:06 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 11:00:18 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_gnl	*find_fd_list(int fd, t_gnl **head)
{
	t_gnl	*new;
	t_gnl	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	new = (t_gnl *)malloc(sizeof (t_gnl));
	if (!new)
		return (0);
	new->fd = fd;
	new->next = NULL;
	new->str = ft_strdup("");
	if (tmp == NULL)
		*head = new;
	else
		tmp->next = new;
	if (!(new->str))
		return ((t_gnl *)ft_free(head, 0, 0, fd));
	return (new);
}

char	*ft_read(int fd, char *str, char *buff)
{
	ssize_t	size;

	size = 1;
	while (size > 0 && !(ft_strchr(str, '\n')))
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
			return (ft_free(0, &str, buff, fd));
		buff[size] = '\0';
		str = ft_strjoin_gnl(str, buff, 0, 0);
		if (!str)
			return (ft_free(0, 0, buff, fd));
	}
	if (str[0] == '\0')
		return (ft_free(0, &str, buff, fd));
	free(buff);
	return (str);
}

char	*get_until_newline(char *str)
{
	char	*tmp;
	ssize_t	i;
	ssize_t	size;
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	size = i + ((size_t)i != len) + 1;
	tmp = (char *)malloc(size);
	if (!tmp)
		return (0);
	tmp[--size] = '\0';
	i = -1;
	while (++i < size)
		tmp[i] = str[i];
	return (tmp);
}

char	*pull_newline(char *str, char *rt, ssize_t i, ssize_t idx)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(len - i + 1);
	if (!tmp)
		return (ft_free(0, &str, rt, -1));
	if (len > (size_t)i)
	{
		while (str[++i])
			tmp[++idx] = str[i];
	}
	tmp[++idx] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_gnl	*head;
	t_gnl			*list;
	char			*buff;
	char			*rt;

	list = find_fd_list(fd, &head);
	if (!list)
		return (0);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (ft_free(&head, &(list->str), 0, fd));
	list->str = ft_read(fd, list->str, buff);
	if (!(list->str))
		return (ft_free(&head, 0, 0, fd));
	rt = get_until_newline(list->str);
	if (!rt)
		return (ft_free(&head, &(list->str), 0, fd));
	list->str = pull_newline(list->str, rt, 0, -1);
	if (!(list->str))
		return (ft_free(&head, 0, 0, fd));
	return (rt);
}
