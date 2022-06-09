/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:27:02 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 06:19:02 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_out(t_cmd command)
{
	while (command.redir && command.redir->path)
	{
		if (command.redir->type == DR_REDIR || command.redir->type == R_REDIR)
			return (1);
		command.redir = command.redir->next;
	}
	return (0);
}

int	ft_check_in(t_cmd command)
{
	while (command.redir && command.redir->path)
	{
		if (command.redir->type == L_REDIR || command.redir->type == HEREDOC)
			return (1);
		command.redir = command.redir->next;
	}
	return (0);
}

int	ft_redir_in(t_cmd *com, int fd[2][2], int red_pipe[2], char *here)
{
	int	redir_status;
	int	fork_id;

	if (com->redir && (com->redir->type == HEREDOC || \
		com->redir->type == L_REDIR))
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			close(red_pipe[0]);
			dup2(red_pipe[1], 1);
			close(red_pipe[1]);
			fd[0][1] = -1;
			redir_status = ft_redir(com->redir, 1);
			if (redir_status == HEREDOC)
				ft_putstr_fd(here, 1);
			ft_close(fd);
			ft_free_all(com);
			exit(0);
		}
	}
	return (1);
}

char	*ft_heredoc_wheel(t_arg *redir, t_cmd *cmd, char *final, char *str)
{
	str = readline("> ");
	if (!str)
		return (final);
	final = ft_strdup("");
	if (!final)
		error_end(3);
	ft_pfree(&cmd, final);
	while (ft_strcmp(str, redir->path))
	{
		final = ft_stdstrjoin(final, str);
		if (!final)
			error_end(3);
		ft_pfree(&cmd, final);
		final = ft_stdstrjoin(final, "\n");
		if (!final)
			error_end(3);
		ft_pfree(&cmd, final);
		free(str);
		str = readline("> ");
		if (!str)
			return (final);
	}
	free(str);
	return (final);
}
