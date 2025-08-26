/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:25:26 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/26 15:25:26 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_cmds(char **argv, int av_index)
{
	char	**command;

	command = ft_split(argv[av_index], ' ');
	if (!command)
		return (clean_mem(NULL, command), NULL);
	return (command);
}

static char	*search_path(char **envp)
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

static char	*join_path(char *raw_path, char **argv, int av_index)
{
	char	*full_path;
	char	**command;

	full_path = ft_strjoin(raw_path, "/");
	if (!full_path)
		return (free(full_path), NULL);
	command = ft_split(argv[av_index], ' ');
	if (!command || !command[0])
		return (clean_mem(full_path, command), NULL);
	full_path = ft_free_and_join(full_path, command[0]);
	if (!full_path)
		return (clean_mem(full_path, command), NULL);
	clean_mem(NULL, command);
	return (full_path);
}

char	*get_path(char **argv, char **envp, int av_index)
{
	char	**arr_path;
	char	*full_path;
	int		i;

	full_path = NULL;
	arr_path = ft_split(search_path(envp), ':');
	if (!arr_path)
		return (NULL);
	i = 0;
	while (arr_path[i])
	{
		if (access(argv[av_index], F_OK | X_OK) == 0)
			return (argv[av_index]);
		if (full_path)
			free(full_path);
		full_path = join_path(arr_path[i], argv, av_index);
		if (!full_path)
			return (clean_mem(full_path, arr_path), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		else
			i++;
	}
	return (clean_mem(full_path, arr_path), NULL);
}
