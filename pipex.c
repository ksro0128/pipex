/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:37:55 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 11:13:42 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first(char *argv[], char *envp[], t_list *list)
{
	char	**pathlist;

	inputfile_open(argv, list);
	if (argv[2][0] == '\0')
	{
		ft_putstr_fd("pipex:: command not found\n", 2);
		exit(127);
	}
	list->option = ft_split(argv[2], ' ');
	if (list->option == NULL)
		exit(1);
	pathlist = make_pathlist(envp);
	list->path = find_path(list->option, pathlist);
	if (dup2(list->inputfile, 0) == -1 || dup2(list->pipe_fd[1], 1) == -1)
		exit(1);
	if (close(list->pipe_fd[0]) == -1 || close(list->pipe_fd[1]) == -1)
		exit(1);
	if (execve(list->path, list->option, envp) == -1)
	{
		perror("pipex:");
		exit(1);
	}
}

void	last(char *argv[], char *envp[], t_list *list)
{
	char	**pathlist;

	outputfile_open(argv, list);
	if (argv[3][0] == '\0')
	{
		ft_putstr_fd("pipex:: command not found\n", 2);
		exit(1);
	}
	list->option = ft_split(argv[3], ' ');
	if (list->option == NULL)
		exit(1);
	pathlist = make_pathlist(envp);
	list->path = find_path(list->option, pathlist);
	if (dup2(list->pipe_fd[0], 0) == -1 || dup2(list->outputfile, 1) == -1)
		exit(1);
	if (close(list->pipe_fd[0]) == -1 || close(list->pipe_fd[1]) == -1)
		exit(1);
	if (execve(list->path, list->option, envp) == -1)
	{
		perror("pipex:");
		exit(1);
	}
}

void	pipex(char *argv[], char *envp[], t_list *list)
{
	int	pid1;
	int	pid2;
	int	status2;

	ft_pipe(list->pipe_fd);
	pid1 = ft_fork();
	if (pid1 == 0)
		first(argv, envp, list);
	pid2 = ft_fork();
	if (pid2 == 0)
		last(argv, envp, list);
	if (close(list->pipe_fd[0]) == -1 || close(list->pipe_fd[1]) == -1)
		exit(1);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status2, 0);
	if (WEXITSTATUS(status2))
		exit(WEXITSTATUS(status2));
	else
		exit(0);
}
