/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:38:31 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 15:43:35 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_list
{
	int		inputfile;
	int		outputfile;
	int		pipe_fd[2];
	int		*multi_pid;
	int		**multi_fd;
	int		argc;
	char	*path;
	char	**option;
}t_list;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
int		ft_fork(void);
void	ft_pipe(int fd[2]);
void	ft_err_print(char *a, char *b, int fd);
void	ft_perror(char *str);
void	inputfile_open(char *argv[], t_list *list);
void	outputfile_open(char *argv[], t_list *list);
char	*ft_strjoin_v2(char *a, char *b);
char	*find_path(char *path[], char *pathlist[]);
char	**make_pathlist(char *envp[]);
void	pipex(char *argv[], char *envp[], t_list *list);

#endif