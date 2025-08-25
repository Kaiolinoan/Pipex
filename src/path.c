/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:17:00 by marvin            #+#    #+#             */
/*   Updated: 2025/08/23 18:17:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_cmds(char **argv, int av_index)
{
	char		**command;

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
	char		*full_path;
	char		**command;

	full_path = ft_strjoin(raw_path, "/");
	if (!full_path)
		return (free(full_path), NULL);
	command = ft_split(argv[av_index], ' ');
	if (!command)
		return (clean_mem(full_path, command), NULL);
	full_path = ft_free_and_join(full_path, command[0]);
	if (!full_path)
		return (clean_mem(full_path, command), NULL);
	int i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
	return (full_path);
}
char	*get_path(char **argv, char **envp, int av_index)
{
	char	**arr_path;
	char	*full_path;
	int		i;
	int		j;
	
	full_path = NULL;
	arr_path = ft_split(search_path(envp), ':');
	if (!arr_path)
		return (clean_mem(NULL, arr_path), NULL);
	i = 0;
	while (arr_path[i])
	{
		if (full_path)
			free(full_path);
		full_path = join_path(arr_path[i], argv, av_index);
		if (!full_path)
			return (free(full_path), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			j = 0;
			while (arr_path[j])
				free(arr_path[j++]);
			free(arr_path);
			return (full_path);
		}
		else
			i++;
	}
	j = 0;
	while (arr_path[j])
		free(arr_path[j++]);
	free(arr_path);
	free(full_path);
	return (NULL);
}
