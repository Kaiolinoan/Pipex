/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:08:01 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/26 16:08:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_free_and_join(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	print_error(char *file, int pipe_fd[2])
{
	write(2, "zsh: ", 5);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(-2);
}

void	clean_mem(char *path, char **matriz)
{
	size_t	i;

	i = 0;
	if (matriz)
		while (matriz[i])
			free(matriz[i++]);
	if (matriz)
		free(matriz);
	if (path)
		free(path);
}

void	free_split(char **str, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(str[i++]);
	free(str);
}
