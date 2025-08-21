/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:36:16 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/21 15:37:56 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_cmds(char **argv, int argc)
{
	char		**command;
	static int	i = 2;

	if (i > argc - 2)
		return (NULL);
	command = ft_split(argv[i], ' ');
	if (!command)
		return (NULL);
	i++;
	return (command);
}

char	*search_path(char **envp)
{
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

char	*join_path(char *raw_path, char **argv, int argc, int av_index)
{
	char		*full_path;
	char		**command;

	if (av_index > argc - 2)
		return (NULL);
	full_path = ft_strjoin(raw_path, "/");
	if (!full_path)
		return (NULL);
	command = ft_split(argv[av_index], ' ');
	if (!command)
		return (NULL);
	full_path = ft_strjoin(full_path, command[0]);
	if (!full_path)
		return (NULL);
	return (full_path);
}
char	*get_path(int argc, char **argv, char **envp)
{
	char	**arr_path;
	char	*full_path;
	static int	av_index = 2;
	int		i;

	arr_path = ft_split(search_path(envp), ':');
	if (!arr_path)
		return (NULL);
	i = 0;
	while (arr_path[i])
	{
		full_path = join_path(arr_path[i], argv, argc, av_index);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
		{
			av_index++;
			printf("path: %s\n", full_path);
			return (full_path);
		}
		else
			i++;
	}
	av_index++;
	printf("path nao encontrado");
	return (NULL);
}