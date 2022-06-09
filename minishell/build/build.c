/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:47:53 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 07:10:07 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	path_search(t_cmd *command, char *path, char **env)
{
	if (!path)
	{
		ft_putstr_fd(command->argum[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_all(command);
		exit(127);
	}
	path = ft_strdup(path);
	if (!path)
		error_end(3);
	ft_free_all(command);
	if (execve(path, command->argum, env) == -1)
	{
		ft_putstr_fd(command->argum[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_all(command);
		exit(1);
	}
}

void	ft_child(t_cmd *command, int fd[2][2], int red_pipe[2], char **env)
{
	char	*path;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (command->redir)
		ft_redir(command->redir, 0);
	if (command->argum)
	{
		ft_pipex(red_pipe, fd, command);
		ft_close(fd);
		ft_system(command, env + 1);
		path = ft_find_command(command, env);
		path_search(command, path, env);
	}
	else
		exit(0);
}

int	ft_wait_processes(int len_processes)
{
	int	status;
	int	exit_status;
	int	wexit;

	exit_status = 1;
	while (len_processes-- > 0)
	{
		wait(&status);
		wexit = WEXITSTATUS(status);
		if (WTERMSIG(status) == SIGSEGV)
		{
			ft_putstr_fd("Error: Segmentation fault\n", 2);
			wexit = 2;
		}
		if (WTERMSIG(status) == SIGABRT)
		{
			ft_putstr_fd("Error: Abort\n", 2);
			wexit = 2;
		}
	}
	return (wexit);
}

int	ft_process_setup(int fd[2][2], int red_pipe[2], int *len_processes)
{
	int	exit_result;

	ft_close(fd);
	close(red_pipe[0]);
	close(red_pipe[1]);
	exit_result = ft_wait_processes(*len_processes);
	*len_processes = 0;
	return (exit_result);
}

int	ft_exec_com(t_cmd *com, char ***env, int fd[2][2], int red_pipe[2])
{
	static int	len_processes = 0;
	int			fork_id;
	char		*heredoc;
	int			retrn;

	heredoc = NULL;
	retrn = ft_system_parent(com, env);
	if (retrn)
		return (retrn - 1);
	if (com->redir)
		heredoc = ft_heredoc(com->redir, com);
	fork_id = fork();
	++len_processes;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (fork_id == 0)
		ft_child(com, fd, red_pipe, *env);
	++len_processes;
	ft_redir_in(com, fd, red_pipe, heredoc);
	if (!com->pipe.out)
		retrn = ft_process_setup(fd, red_pipe, &len_processes);
	ft_free_all(com);
	ft_close_pipe(fd, *com);
	return (retrn);
}
