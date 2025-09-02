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

#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
    t_data data;
    int current;
    int status;
    int exit_status;

    if (argc < 5)
        return (EXIT_FAILURE);
    current = 2;
    // data = initialize(argc, argv, envp);
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
        data.in = open(data.argv[1], O_RDONLY);
	if (data.in < 0)
		(print_error(data.argv[1]), close_and_exit(data.pipe_fd1));
    data.out = open(data.argv[data.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.out < 0)
		(print_error(data.argv[data.argc - 1]), close_and_exit(data.pipe_fd1));
    
    int i;

    i = 2;
    while (i <= data.argc - 2)
    {
        if (i % 2 == 0)
        {
            if (pipe(data.pipe_fd1) < 0)
                return (perror("Error"), EXIT_FAILURE);
        }
        else
            if (pipe(data.pipe_fd2) < 0)
                return (perror("Error"), EXIT_FAILURE);
        i++;
    }
    while (current < argc - 1)
    {
        if ((data.child = fork()) < 0)
            return (perror("Error"), EXIT_FAILURE);
        else if (data.child == 0)
            child(data, current);
        current++;
    }
    if (data.child > 0)
    {
        (close(data.pipe_fd1[0]), close(data.pipe_fd1[1]));
	    (close(data.pipe_fd2[0]), close(data.pipe_fd2[1]));
	    waitpid(data.child, &status, 0);
	    exit_status = WEXITSTATUS(status); 
    }
    return (exit_status);
}
