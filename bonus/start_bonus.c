/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:51:59 by marvin            #+#    #+#             */
/*   Updated: 2025/09/01 12:51:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int    load_pipes(t_data data)
{
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
    return (0);
}

static void open_files(t_data data)
{
    data.in = open(data.argv[1], O_RDONLY);
	if (data.in < 0)
		(print_error(data.argv[1]), close_and_exit(data.pipe_fd1));
    data.out = open(data.argv[data.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.out < 0)
		(print_error(data.argv[data.argc - 1]), close_and_exit(data.pipe_fd1));
}

t_data    initialize(int argc, char **argv, char **envp)
{
    t_data data;
    
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    load_pipes(data);
    open_files(data);
    return (data);
}