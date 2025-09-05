/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:14:40 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 15:14:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    here_doc(t_data *data)
{
    char *limiter;
    char *line;

    line =  NULL;
    limiter = data->argv[2];
    if (pipe(data->pipe_fd1) < 0)
        return ;
    while (1)
    {
        line = get_next_line(0);
        if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 ) && (line[ft_strlen(limiter)] == '\n'))
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, data->pipe_fd1[1]); 
        free(line);
    }
    ft_close(&data->pipe_fd1[1]);
}
