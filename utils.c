/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:33:54 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:08:00 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (write(fd, s, ft_strlen(s)) == -1)
		exit(1);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	size_t	size;
	char	*tmp;

	i = 0;
	size = ft_strlen(s1);
	tmp = (char *) malloc(size + 1);
	if (!tmp)
		exit(1);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*tmp;
	size_t	i;

	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tmp = (char *) malloc(sizeof (char) * (s1_len + s2_len + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (i < s1_len)
	{
		tmp[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		tmp[i] = s2[i - s1_len];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
