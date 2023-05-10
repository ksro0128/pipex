/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:10:25 by surkim            #+#    #+#             */
/*   Updated: 2023/05/09 13:45:51 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_list	list;

	if (argc < 5)
		return (1);
	if (ft_strcmp_v1(argv[1], "here_doc") == 0 && argc == 6)
		ft_here_doc(argv, envp, &list);
	else if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc != 6)
		return (1);
	else if (argc == 5)
		pipex(argv, envp, &list);
	else if (argc > 5)
		multipipex(argc, argv, envp, &list);
}
