/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:52:53 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:06:14 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	multi_first(int argc, char *argv[], char *envp[], t_list *list)
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
	if (dup2(list->inputfile, 0) == -1 || dup2(list->multi_fd[0][1], 1) == -1)
		exit(1);
	ft_multi_close_all(argc, list);
	if (execve(list->path, list->option, envp) == -1)
	{
		perror("pipex:");
		exit(1);
	}
}

void	multi_mid_exec(int i, char *argv[], char *envp[], t_list *list)
{
	char	**pathlist;

	if (argv[i + 2][0] == '\0')
	{
		ft_putstr_fd("pipex:: command not found\n", 2);
		exit(127);
	}
	list->option = ft_split(argv[i + 2], ' ');
	if (list->option == NULL)
		exit(1);
	pathlist = make_pathlist(envp);
	list->path = find_path(list->option, pathlist);
	if (dup2(list->multi_fd[i - 1][0], 0) == -1 || \
	dup2(list->multi_fd[i][1], 1) == -1)
		exit(1);
	ft_multi_close_all(list->argc, list);
	if (execve(list->path, list->option, envp) == -1)
	{
		perror("pipex:");
		exit(1);
	}
}

void	multi_mid(int argc, char *argv[], char *envp[], t_list *list)
{
	int	i;

	i = 1;
	while (i < argc - 4)
	{
		list->multi_pid[i] = ft_fork();
		if (list->multi_pid[i] == 0)
			multi_mid_exec(i, argv, envp, list);
		i++;
	}
}

void	multi_last(int argc, char *argv[], char *envp[], t_list *list)
{
	char	**pathlist;

	outputfile_open_multi(argc, argv, list);
	if (argv[argc - 2][0] == '\0')
	{
		ft_putstr_fd("pipex:: command not found\n", 2);
		exit(1);
	}
	list->option = ft_split(argv[argc - 2], ' ');
	if (list->option == NULL)
		exit(1);
	pathlist = make_pathlist(envp);
	list->path = find_path(list->option, pathlist);
	if (dup2(list->multi_fd[argc - 5][0], 0) == -1 || \
	dup2(list->outputfile, 1) == -1)
		exit(1);
	ft_multi_close_all(argc, list);
	if (execve(list->path, list->option, envp) == -1)
	{
		perror("pipex:");
		exit(1);
	}
}

void	multipipex(int argc, char *argv[], char *envp[], t_list *list)
{
	int	i;
	int	status;

	list->argc = argc;
	list->multi_pid = make_pid(argc);
	list->multi_fd = make_pipe(argc);
	list->multi_pid[0] = ft_fork();
	if (list->multi_pid[0] == 0)
		multi_first(argc, argv, envp, list);
	multi_mid(argc, argv, envp, list);
	list->multi_pid[argc - 4] = ft_fork();
	if (list->multi_pid[argc - 4] == 0)
		multi_last(argc, argv, envp, list);
	i = 0;
	ft_multi_close_all(argc, list);
	multi_waitpid(argc, list);
	waitpid(list->multi_pid[argc - 4], &status, WNOHANG);
	if (WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
	else
		exit(0);
}
