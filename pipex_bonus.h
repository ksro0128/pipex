/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:44:03 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 15:43:39 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

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

typedef struct s_gnl{
	int				fd;
	char			*str;
	struct s_gnl	*next;
}t_gnl;

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
char	*ft_strjoin_free_first(char *s1, char *s2);
char	*make_here_doc_file(void);
void	here_doc_write(char *argv[], t_list *list);
void	here_doc_outputfile_open(char *argv[], t_list *list);
void	ft_here_doc(char *argv[], char *envp[], t_list *list);
int		*make_pid(int argc);
int		**make_pipe(int argc);
void	ft_multi_close_all(int argc, t_list *list);
void	outputfile_open_multi(int argc, char *argv[], t_list *list);
void	multi_waitpid(int argc, t_list *list);
void	multipipex(int argc, char *argv[], char *envp[], t_list *list);
int		ft_strcmp_v1(const char *s1, const char *s2);
int		ft_strcmp_v2(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2, size_t s1_len, size_t s2_len);
char	*ft_free(t_gnl **list, char **s1, char *s2, int fd);
void	remove_list(t_gnl **head, int fd);
void	pipex(char *argv[], char *envp[], t_list *list);

#endif