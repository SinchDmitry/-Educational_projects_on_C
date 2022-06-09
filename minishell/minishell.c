/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:20 by aarchiba          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/10 07:12:28 by aconchit         ###   ########.fr       */
=======
/*   Updated: 2022/02/10 06:56:44 by aarchiba         ###   ########.fr       */
>>>>>>> edcdd157718b501d14d275eee5be33ee7d7e43c7
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_start(char *str, char ***env)
{
	t_data	*tmp;
	t_cmd	*tmp1;
	t_cmd	*cmd;

	save_point(NULL, 4);
	tmp1 = NULL;
	if (!str)
	{
		ft_putstr_fd("exit\n", 1);
		return (1);
	}
	else
		str = ft_isspace_strtrim(str);
	add_history(str);
	save_point(str, 2);
	tmp = sym_parse(str);
	if (tmp && tmp->parse_error == 1)
	{
		error_end(2);
		return (0);
	}
	cmd = cmd_parse(tmp1, tmp, env);
	error_end(4);
	return (0);
}

static int	gen_shell(t_cmd *command)
{
	if (command->argum && !ft_strncmp(command->argum[0], \
		"exit", 4))
	{
		ft_putstr_fd("exit\n", 1);
		if (command->argum[1] && command->argum[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (0);
		}
		if (command->argum[1])
			exit(ft_atoi(command->argum[1]));
		else
			exit(0);
	}
	return (1);
}

static void	sub_shell(t_cmd *command, char ***env)
{
	if (command && command->sub)
	{
		if (!fork())
		{
			ft_start(command->args->path, env);
			exit(0);
		}
		wait(NULL);
	}
}

int	minishell(t_cmd *command, char ***env, int fd[2][2], int red_fd[2])
{
	int		execution_status;
	char	*execution_status_char;

	command->free = NULL;
	if (!*(command->argum[0]))
		return (0);
	if (command && !command->sub)
	{
		if (!gen_shell(command))
			return (0);
		ft_pipe_setting(fd, red_fd, command);
		execution_status = ft_exec_com(command, env, fd, red_fd);
		free(**env);
		execution_status_char = ft_itoa(execution_status);
		**env = ft_stdstrjoin("?=", execution_status_char);
		free(execution_status_char);
		if (execution_status)
			return (0);
	}
	sub_shell(command, env);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	env = ft_new_env(env);
	while (1)
	{
		ft_signal();
		save_point(NULL, 4);
		str = readline("\e[1;32mMINISHELL$\e[0;37m ");
		if (ft_start(str, &env))
			break ;
	}
	ft_free_env(env);
	return (0);
}
