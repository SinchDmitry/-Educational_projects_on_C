/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:33 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 04:18:23 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_system(t_cmd *command, char **env)
{
	if (!ft_strcmp(command->argum[0], "echo"))
	{
		ft_echo(command->argum);
		exit(0);
	}
	if (!ft_strcmp(command->argum[0], "env"))
	{
		ft_env(env);
		exit(0);
	}
	if (!ft_strcmp(command->argum[0], "pwd"))
	{
		ft_pwd(env);
		exit(0);
	}
	if (!ft_strcmp(command->argum[0], "export"))
	{
		ft_export(&env, &command->argum[1]);
		exit(0);
	}
}

int	ft_system_parent(t_cmd *command, char ***env)
{
	if (command->argum && !ft_strcmp(command->argum[0], "cd"))
	{
		ft_cd(command->argum[1], env);
		return (1);
	}
	if (!ft_strcmp(command->argum[0], "export") && command->argum[1])
		return (ft_export(env, &command->argum[1]) + 1);
	if (!ft_strcmp(command->argum[0], "unset"))
		return (ft_unset(env, &command->argum[1], 1) + 1);
	return (0);
}
