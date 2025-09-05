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

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/libft.h"
# include <errno.h>
# include <sys/wait.h>
#include <stdbool.h>

typedef struct s_data
{
    int     in;
    int     out;
    int     pipe_fd1[2];
    int     pipe_fd2[2];
	int		child;
	int		argc;
    char    **argv;
    char    **envp;
    bool    here_doc;
}	t_data;

typedef struct s_split
{
	size_t	arr_i;
	size_t	mat_index;
}	t_split;

void    iniatialize_vars(t_data *data, int argc, char **argv, char**envp);
bool    create_pipes(t_data *data, int current);
char	*get_path(char **argv, char **envp, int av_index);
char	*ft_free_and_join(char *s1, char *s2);
char	**get_cmds(char **argv, int av_index);
void	clean_mem(char *path, char **cmd);
void	children(t_data *data, int *current);
void	close_and_exit(int pipe_fd[2]);
void	print_error(char *file);
void    close_all(t_data *data);
void    ft_close(int *fd);
void    close_main(t_data *data);
void    here_doc(t_data *data);


// split related
void	free_split(char **str, size_t count);
char	**ft_split_quotes(char const *s, char c);

#endif