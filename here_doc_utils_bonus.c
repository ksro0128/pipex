/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:43:11 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 14:12:14 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_free_first(char *s1, char *s2)
{
	char	*rt;

	rt = ft_strjoin(s1, s2);
	free(s1);
	return (rt);
}

char	*make_here_doc_file(void)
{
	char	*here_doc;

	here_doc = ft_strdup(".here_doc");
	if (access(here_doc, F_OK) != 0)
		return (here_doc);
	else
	{
		while (access(here_doc, F_OK) == 0)
		{
			here_doc = ft_strjoin_free_first(here_doc, "tmp");
			if (here_doc == NULL)
				exit(1);
		}
		return (here_doc);
	}
}

void	here_doc_open_unlink(char *here_doc, t_list *list)
{
	if (close(list->inputfile) == -1)
		exit(1);
	list->inputfile = open(here_doc, O_RDONLY);
	if (list->inputfile == -1 || unlink(here_doc) == -1)
		exit(1);
}

void	here_doc_write(char *argv[], t_list *list)
{
	char	*tmp;
	char	*here_doc;

	here_doc = make_here_doc_file();
	list->inputfile = open(here_doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (list->inputfile == -1)
		exit(1);
	while (1)
	{
		if (write(0, "pipe here_doc> ", 16) == -1)
			exit(1);
		tmp = get_next_line(0);
		if (ft_strcmp_v2(tmp, argv[2]) == 0)
		{
			free(tmp);
			break ;
		}
		if (write(list->inputfile, tmp, ft_strlen(tmp)) == -1)
			exit(1);
		free(tmp);
	}
	here_doc_open_unlink(here_doc, list);
	free(here_doc);
}

void	here_doc_outputfile_open(char *argv[], t_list *list)
{
	list->outputfile = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (list->outputfile == -1)
	{
		ft_perror(argv[4]);
		exit(1);
	}
}
