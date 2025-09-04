/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:14:40 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 15:14:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void iniatialize_vars(t_data *data, int argc, char **argv, char**envp)
{
    data->argc = argc;
    data->argv = argv;
    data->envp = envp;
    data->in = -1;
    data->out = -1;
    data->pipe_fd1[0] = -1;
    data->pipe_fd1[1] = -1;
    data->pipe_fd2[0] = -1;
    data->pipe_fd2[1] = -1;
}  

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && (i < n))
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

void    here_doc(t_data data)
{
    char *store;
    char *limiter;
    char *str;

    store = NULL;
    str = NULL;
    limiter = data.argv[2];
    while (1)
    {
        str = get_next_line(0);
        store = ft_strjoin(store, str);
        if ((ft_strncmp(str, limiter, ft_strlen(limiter)) == 0 ) && (str[ft_strlen(limiter)] == '\n'))
            break ;
    }
    
}
 int main(int argc, char **argv, char **envp)
 {
    t_data data;
    iniatialize_vars(&data , argc, argv, envp);
    here_doc(data);
 }