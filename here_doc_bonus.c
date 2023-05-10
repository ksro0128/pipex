/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:47:38 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:04:21 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_here_doc(char *argv[], char *envp[], t_list *list)
{
	char	**pathlist;

	if (argv[3][0] == '\0')
	{
		ft_putstr_fd("pipex:: command not found\n", 2);
		exit(127);
	}
	list->option = ft_split(argv[3], ' ');
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

void	last_here_doc(char *argv[], char *envp[], t_list *list)
{
	char	**pathlist;

	here_doc_outputfile_open(argv, list);
	if (argv[4][0] == '\0')
	{
		ft_putstr_fd("pipex:: command not found\n", 2);
		exit(1);
	}
	list->option = ft_split(argv[4], ' ');
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

void	ft_here_doc(char *argv[], char *envp[], t_list *list)
{
	int	pid1;
	int	pid2;
	int	status2;

	here_doc_write(argv, list);
	ft_pipe(list->pipe_fd);
	pid1 = ft_fork();
	if (pid1 == 0)
		first_here_doc(argv, envp, list);
	pid2 = ft_fork();
	if (pid2 == 0)
		last_here_doc(argv, envp, list);
	if (close(list->pipe_fd[0]) == -1 || close(list->pipe_fd[1]) == -1)
		exit(1);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status2, 0);
	if (WEXITSTATUS(status2))
		exit(WEXITSTATUS(status2));
	else
		exit(0);
}
