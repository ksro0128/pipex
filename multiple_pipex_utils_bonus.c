/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipex_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:50:37 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:07:02 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	*make_pid(int argc)
{
	int	*pid;

	pid = (int *)malloc(sizeof (int) * (argc - 3));
	if (pid == NULL)
		exit(1);
	return (pid);
}

int	**make_pipe(int argc)
{
	int	**fd;
	int	i;

	fd = (int **)malloc(sizeof (int *) * (argc - 4));
	if (fd == NULL)
		exit(1);
	i = 0;
	while (i < argc - 4)
	{
		fd[i] = (int *)malloc(sizeof (int) * 2);
		if (fd[i] == NULL)
			exit(1);
		i++;
	}
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(fd[i]) == -1)
			exit(1);
		i++;
	}
	return (fd);
}

void	ft_multi_close_all(int argc, t_list *list)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		if (close(list->multi_fd[i][0]) == -1 || \
		close(list->multi_fd[i][1]) == -1)
			exit(1);
		i++;
	}
}

void	outputfile_open_multi(int argc, char *argv[], t_list *list)
{
	list->outputfile = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (list->outputfile == -1)
	{
		ft_perror(argv[argc - 1]);
		exit(1);
	}
}

void	multi_waitpid(int argc, t_list *list)
{
	int	i;

	i = 0;
	while (i < argc - 5)
	{
		waitpid(list->multi_pid[i], NULL, WNOHANG);
		i++;
	}
}
