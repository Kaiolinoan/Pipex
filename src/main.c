/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:38:42 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/21 17:42:59 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;
	int		pipe_fd[2];
	int		commands_count;
	char	*path;
	char	**cmd;
	int		status;
	int		wpid;

	i = 1;
	if (argc != 5)
		return (-1);
	commands_count = argc - 3;
	data.stdin = dup(0);
	data.stdout = dup(1);
	while (i <= commands_count)
	{
		pipe(pipe_fd);
		data.pid = fork();
		if (data.pid < 0)
			write(2, "Erro\n", 5);
		else if (data.pid == 0)
		{
			if (i == 1)
				data.fd = open(argv[1], O_RDONLY);
			else if (i == commands_count)
				data.fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			if (data.fd < 0)
				(perror("zsh"));
			// write(2, "Nao deu para abrir o arquivo\n", 29);
			if (i == 1)
				(dup2(data.fd, 0), dup2(pipe_fd[1], 1));
			else if (i == commands_count)
				(dup2(pipe_fd[0], 0), dup2(data.fd, 1));
			close(data.fd);
			path = get_path(argc, argv, envp);
			cmd = get_cmds(argv, argc);
			execve(path, cmd, envp);
			write(2, "execve falhou\n", 14);
			exit(-1);
		}
		i++;
	}
	if (data.pid > 0)
	{
		while (1)
		{
			wpid = waitpid(data.pid, &status, 0);
			if (wpid <= 0)
				break ;
		}
				// loop para quantidade de filhos
	}
	// get_path(argc, argv, envp);
	return (0);
}
