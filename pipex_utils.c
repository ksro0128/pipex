/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:05:37 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:07:45 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	return (pid);
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		exit(1);
}

void	ft_err_print(char *a, char *b, int fd)
{
	ft_putstr_fd("pipex: ", fd);
	ft_putstr_fd(a, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(b, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_perror(char *str)
{
	ft_putstr_fd("pipex: ", 2);
	perror(str);
}
