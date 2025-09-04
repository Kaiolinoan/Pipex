/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:29:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/03 17:29:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_close(int *fd)
{
	if ((*fd) != -1)
		close(*fd);
	(*fd) = -1;
}

void close_all(t_data *data)
{
	if (data->pipe_fd1[0] != -1)
		ft_close(&data->pipe_fd1[0]);
	if (data->pipe_fd1[1] != -1)
		ft_close(&data->pipe_fd1[1]);
	if (data->pipe_fd2[0] != -1)
		ft_close(&data->pipe_fd2[0]);
	if (data->pipe_fd2[1] != -1)
		ft_close(&data->pipe_fd2[1]);
}

void    close_main(t_data *data)
{
    perror("Error");
    close_all(data);
    exit(EXIT_FAILURE);
}