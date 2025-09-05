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

void iniatialize_vars(t_data *data, int argc, char **argv, char**envp)
{
    data->argc = argc;
    data->argv = argv;
    data->envp = envp;
    data->in = -1;
    data->out = -1;
    data->pipe_fd1[0] = -1;
    data->pipe_fd1[1] = -1;
    data->pipe_fd2[0] = -1;
    data->pipe_fd2[1] = -1;
    data->here_doc = false;
}   

bool create_pipes(t_data *data, int current)
{
    if (current != data->argc - 2)
    {
        if (current % 2 == 0)
        {
            if (pipe(data->pipe_fd1) < 0)
                return (false);
        }
        else
            if (pipe(data->pipe_fd2) < 0)
                return (false);
    }
    return (true);
}
