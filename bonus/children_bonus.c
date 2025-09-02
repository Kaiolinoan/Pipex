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
void manage_fds(t_data data, int input, int output)
{
	dup2(input, 0);
	dup2(output, 1);
	close(data.pipe_fd1[0]);
	close(data.pipe_fd1[1]);
	close(data.pipe_fd2[0]);
	close(data.pipe_fd2[1]);
	close(data.in);
	close(data.out);
}

static void exec_commands(t_data data, int current)
{
	char	*path;
	char	**cmd;

	path = get_path(data.argv, data.envp, current);
	cmd = get_cmds(data.argv, current);
	if (!path || !cmd || !(*cmd))
	{
		write(2, "zsh: command not found: ", 24);
		(write(2, data.argv[current], ft_strlen(data.argv[current])), write(2, "\n", 1));
		(clean_mem(path, cmd), exit(EXIT_FAILURE));
	}
	execve(path, cmd, data.envp);
	print_error(data.argv[current]);
	clean_mem(path, cmd);
	exit(EXIT_FAILURE);
}

void	children(t_data data, int current)
{
	if (current == 2)
		(manage_fds(data, data.in, data.pipe_fd1[1]), close(data.in));
	else if (current == data.argc - 2)
	{
		if (current % 2 == 0)
			manage_fds(data, data.pipe_fd2[0], data.out);

		else 
			manage_fds(data, data.pipe_fd1[0], data.out);
		close(data.out);
	}
	else
	{
		if (current % 2 == 0)
			manage_fds(data, data.pipe_fd2[0], data.pipe_fd1[1]);
		else
			manage_fds(data, data.pipe_fd1[0], data.pipe_fd2[1]);
	}
	exec_commands(data, current);
}


