/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:49:57 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 04:30:03 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_bin(char *path)
{
	while (*path)
	{
		if (*path == '/')
			return (1);
		++path;
	}
	return (0);
}

char	*ft_return_path(char **paths, char *arg, t_cmd *command)
{
	int		index;
	char	*check_path;

	index = 0;
	while (paths[index])
	{
		check_path = ft_stdstrjoin(paths[index], arg);
		if (!check_path)
			error_end(3);
		ft_pfree(&command, check_path);
		if (!access(check_path, 1))
			return (check_path);
		++index;
	}
	return (NULL);
}

char	*ft_get_env(char **env, char *str)
{
	while (*env)
	{
		if (!ft_strncmp(str, *env, ft_strlen(str)))
			return ((*env) + 5);
		env++;
	}
	return (NULL);
}

char	*ft_find_command(t_cmd *command, char **env)
{
	char	*path;
	char	**paths;
	char	*arg;

	if (!access(command->argum[0], 1))
	{
		if (!ft_check_bin(command->argum[0]))
			return (NULL);
		return (command->argum[0]);
	}
	path = ft_get_env(env, "PATH=");
	paths = ft_split(path, ':');
	if (!paths)
		error_end(3);
	ft_ppfree(&command, paths);
	arg = ft_stdstrjoin("/", command->argum[0]);
	if (!arg)
		error_end(3);
	ft_pfree(&command, arg);
	return (ft_return_path(paths, arg, command));
}
