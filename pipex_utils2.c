/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:09:19 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:07:53 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	inputfile_open(char *argv[], t_list *list)
{
	list->inputfile = open(argv[1], O_RDONLY);
	if (list->inputfile == -1)
	{
		ft_perror(argv[1]);
		exit(1);
	}
}

void	outputfile_open(char *argv[], t_list *list)
{
	list->outputfile = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (list->outputfile == -1)
	{
		ft_perror(argv[4]);
		exit(1);
	}
}

char	*ft_strjoin_v2(char *a, char *b)
{
	char	*tmp;
	char	*rt;

	tmp = ft_strjoin(a, "/");
	if (tmp == NULL)
		exit(1);
	rt = ft_strjoin(tmp, b);
	if (rt == NULL)
		exit(1);
	free(tmp);
	return (rt);
}

char	*find_path(char *path[], char *pathlist[])
{
	char	*rt;
	int		i;

	if (path[0][0] == '/' || path[0][0] == '.')
		return (ft_strdup(path[0]));
	i = 0;
	while (pathlist[i] != NULL)
	{
		rt = ft_strjoin_v2(pathlist[i], path[0]);
		if (access(rt, X_OK) == 0)
			return (rt);
		free(rt);
		i++;
	}
	ft_err_print(path[0], "command not found", 2);
	exit(127);
}

char	**make_pathlist(char *envp[])
{
	char	**pathlist;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
	{
		ft_err_print("", "command not found", 2);
		exit(127);
	}
	envp[i] += 5;
	pathlist = ft_split(envp[i], ':');
	if (pathlist == NULL)
		exit(1);
	return (pathlist);
}
