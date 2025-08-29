/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:19:45 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/29 15:19:45 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <errno.h>
# include <sys/wait.h>

typedef struct s_data
{
	pid_t	pid;
	int		fd;
	int		child1;
	int		child2;
}	t_data;

typedef struct s_split
{
	size_t	arr_i;
	size_t	mat_index;
}	t_split;

void	child1(t_data data, char **argv, char **envp, int pipe_fd[2]);
void	child2(t_data data, char **argv, char **envp, int pipe_fd[2]);
char	*get_path(char **argv, char **envp, int av_index);
char	*ft_free_and_join(char *s1, char *s2);
char	**get_cmds(char **argv, int av_index);
void	clean_mem(char *path, char **cmd);
void	close_and_exit(int pipe_fd[2]);
void	print_error(char *file);

// split related
void	free_split(char **str, size_t count);
char	**ft_split_quotes(char const *s, char c);

#endif