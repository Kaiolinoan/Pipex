/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 21:11:52 by marvin            #+#    #+#             */
/*   Updated: 2025/08/22 21:11:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void clean_mem(char *path, char **matriz)
{
	size_t i;

	i = 0;
	while (matriz[i])
		free(matriz[i++]);
	if (matriz)
		free(matriz);
	if (path)
		free(path);
}

void child1(t_data data, char **argv, char **envp, int pipe_fd[2])
{
	char	*path;
	char	**cmd;

	data.fd = open(argv[1], O_RDONLY);
	if (data.fd < 0)
		print_error(argv[1], pipe_fd);
	close(pipe_fd[0]);
	dup2(data.fd, 0);
	dup2(pipe_fd[1],1);
	close(data.fd);
	close(pipe_fd[1]);
	path = get_path(argv, envp, 2);
	cmd = get_cmds(argv, 2);
	if (!path || !cmd || !(*cmd))
	{
		write(2, "zsh: command not found: ", 24);
		(write(2, argv[2], ft_strlen(argv[2])), write(2, "\n", 1));
		clean_mem(path, cmd);
		exit(-1);
	}
	execve(path, cmd, envp);
	perror("zsh");
	clean_mem(path, cmd);
	exit(-1);
}

void child2(t_data data, char **argv, char **envp, int pipe_fd[2])
{
	char	*path;
	char	**cmd;

	data.fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.fd < 0)
		print_error(argv[4], pipe_fd);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	dup2(data.fd, 1);
	close(data.fd);
	close(pipe_fd[0]);
	path = get_path(argv, envp, 3);
	cmd = get_cmds(argv, 3);
	if (!path || !cmd || !(*cmd))
	{
		write(2, "zsh: command not found: ", 24);
		(write(2, argv[3], ft_strlen(argv[3])), write(2, "\n", 1));
		clean_mem(path, cmd);
		exit(-1);
	} 
	execve(path, cmd, envp);
	perror("zsh");
	clean_mem(path, cmd);
	exit(-1);
}

