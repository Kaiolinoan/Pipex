/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:21:11 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/29 15:21:11 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		pipe_fd[2];
	int		status1;
	int		status2;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) < 0)
		return (perror("Error"), -1);
	data.child1 = fork();
	if (data.child1 < 0)
		return (perror("Error"), -1);
	else if (data.child1 == 0)
		child1(data, argv, envp, pipe_fd);
	data.child2 = fork();
	if (data.child2 < 0)
		return (perror("Error"), -1);
	else if (data.child2 == 0)
		child2(data, argv, envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(data.child1, &status1, 0);
	waitpid(data.child2, &status2, 0);
	return (0);
}
