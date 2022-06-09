/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:33:00 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 00:38:28 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipex(int red_pipe[2], int fd[2][2], t_cmd *command)
{
	if (ft_check_out(*command))
		command->pipe.out = 0;
	if (ft_check_in(*command))
		command->pipe.in = 0;
	if (command->pipe.out == 1)
	{
		close(fd[0][0]);
		fd[0][0] = -1;
		dup2(fd[0][1], 1);
	}
	if (command->pipe.in == 1)
	{
		dup2(fd[1][0], 0);
		close(fd[1][1]);
		fd[1][1] = -1;
		close(fd[0][1]);
		fd[0][1] = -1;
	}
	if (ft_check_in(*command))
	{
		close(red_pipe[1]);
		dup2(red_pipe[0], 0);
		close(red_pipe[0]);
	}
	return (1);
}

int	ft_close(int fd[2][2])
{
	if (fd[0][0] != -1)
		close(fd[0][0]);
	if (fd[0][1] != -1)
		close(fd[0][1]);
	if (fd[1][0] != -1)
		close(fd[1][0]);
	if (fd[1][1] != -1)
		close(fd[1][1]);
	fd[0][0] = -1;
	fd[0][1] = -1;
	fd[1][0] = -1;
	fd[1][1] = -1;
	return (1);
}

int	ft_close_pipe(int fd[2][2], t_cmd command)
{
	if (command.pipe.in == 1)
	{
		if (fd[1][0] != -1)
			close(fd[1][0]);
		fd[1][0] = -1;
		if (fd[1][1] != -1)
			close(fd[1][1]);
		fd[1][1] = -1;
	}
	return (1);
}

int	ft_pipe_setting(int fd[2][2], int red_fd[2], t_cmd *command)
{
	if (command->redir)
		pipe(red_fd);
	if (command->pipe.in == 1)
	{	
		fd[1][0] = dup(fd[0][0]);
		fd[1][1] = dup(fd[0][1]);
		close(fd[0][0]);
		fd[0][0] = -1;
		close(fd[0][1]);
		fd[0][1] = -1;
	}
	if (command->pipe.out == 1)
	{
		pipe(fd[0]);
	}
	return (1);
}
