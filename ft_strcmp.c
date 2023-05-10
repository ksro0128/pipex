/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:59:08 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:05:38 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp_v1(const char *s1, const char *s2)
{
	int	s1len;
	int	s2len;
	int	i;

	if (!s1 || !s2)
		return (1);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len != s2len)
		return (1);
	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp_v2(const char *s1, const char *s2)
{
	int	s1len;
	int	s2len;
	int	i;

	if (!s1 || !s2)
		return (1);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len != s2len + 1)
		return (1);
	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
