/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:25:17 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/26 15:25:17 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void manage_fds(t_data *data, int input, int output)
{
	dup2(input, 0);
	dup2(output, 1);
	close_all(data);
}

static void exec_commands(t_data *data, int current)
{
	char	*path;
	char	**cmd;

	path = get_path(data->argv, data->envp, current);
	cmd = get_cmds(data->argv, current);
	if (!path || !cmd || !(*cmd))
	{
		write(2, "zsh: command not found: ", 24);
		(write(2, data->argv[current], ft_strlen(data->argv[current])), write(2, "\n", 1));
		(clean_mem(path, cmd), exit(EXIT_FAILURE));
	}
	execve(path, cmd, data->envp);
	print_error(data->argv[current]);
	clean_mem(path, cmd);
	close_all(data);
	exit(EXIT_FAILURE);
}

void	children(t_data *data, int current)
{
	if (current == 2)
	{
		data->in = open(data->argv[1], O_RDONLY);
		if (data->in < 0)
			(print_error(data->argv[1]), close_and_exit(data->pipe_fd1));
		(manage_fds(data, data->in, data->pipe_fd1[1]), ft_close(&data->in));
	}
	else if (current == data->argc - 2)
	{
		data->out = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out < 0)
			(print_error(data->argv[data->argc - 1]), close_and_exit(data->pipe_fd1));
		if (current % 2 == 0)
			(manage_fds(data, data->pipe_fd2[0], data->out), ft_close(&data->out));
		else 
			(manage_fds(data, data->pipe_fd1[0], data->out), ft_close(&data->out));
	}
	else
	{
		if (current % 2 == 0)
			manage_fds(data, data->pipe_fd2[0], data->pipe_fd1[1]);
		else
			manage_fds(data, data->pipe_fd1[0], data->pipe_fd2[1]);
	}
	exec_commands(data, current);
}


