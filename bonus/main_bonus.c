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

    if (argc < 5)
        return (EXIT_FAILURE);
    iniatialize_vars(&data, argc, argv, envp);
    if (!ft_strncmp(argv[1], "here_doc", 8))
    {
        here_doc(&data);
        data.here_doc = true;
    }
    current = 2;
    while (current <= argc - 2)
    {
        if (create_pipes(&data, current) == false)
            close_main(&data);
        if ((data.child = fork()) < 0)
            close_main(&data);
        else if (data.child == 0)
            children(&data, &current);
        else 
            if (current % 2 == 0)
                ft_close(&data.pipe_fd1[1]), ft_close(&data.pipe_fd2[0]);
            else
                ft_close(&data.pipe_fd1[0]), ft_close(&data.pipe_fd2[1]);
        current++;
    }
	waitpid(data.child, &status, 0);
    return (WEXITSTATUS(status));
}
