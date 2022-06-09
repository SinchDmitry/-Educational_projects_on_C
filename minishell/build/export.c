/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:23:33 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/10 05:28:27 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_sort_env(char **sort_env, int max)
{
	int		index;
	int		sort_index;
	char	*temp;

	sort_index = 0;
	while (sort_index < max - 1)
	{
		index = 0;
		while (index < max - 1)
		{
			if (ft_strcmp(sort_env[sort_index], sort_env[index]) < 0)
			{
				temp = sort_env[sort_index];
				sort_env[sort_index] = sort_env[index];
				sort_env[index] = temp;
			}
			++index;
		}
		++sort_index;
	}
	sort_env[max - 1] = NULL;
	return (sort_env);
}

int	ft_print_sort_env(char **env)
{
	int		max;
	char	**sort_env;
	int		sort_index;

	sort_index = 0;
	max = ft_max(env);
	sort_env = (char **)malloc(sizeof(char *) * (max));
	if (!sort_env)
		error_end(3);
	while (sort_index < max)
	{
		sort_env[sort_index] = env[sort_index];
		++sort_index;
	}
	sort_env = ft_sort_env(sort_env, max);
	while (*sort_env)
		printf("%s\n", *(sort_env++));
	return (1);
}

char	**ft_delete_var(char **env, char **arg)
{
	char	**tmp;
	char	**old_env;

	tmp = (char **)malloc(sizeof(char *) * (ft_max(arg) + 2));
	if (!tmp)
		error_end(3);
	tmp = ft_new_arg(arg, tmp);
	old_env = env;
	ft_unset(&env, tmp, 0);
	ft_free_env(tmp);
	ft_free_env(old_env);
	return (env);
}

char	**ft_env_export(char **new_env, char **env, char **arg, int *status)
{
	int		index;
	int		env_index;

	env++;
	index = 0;
	env_index = 0;
	new_env[index++] = ft_stdstrjoin("?=", "0");
	if (!new_env[index - 1])
		error_end(3);
	while (*arg)
	{
		new_env = ft_exp_utils(arg, status, &index, new_env);
		++arg;
	}
	while (env[env_index])
	{
		new_env[index++] = ft_strdup(env[env_index++]);
		if (!new_env[index - 1])
			error_end(3);
	}
	new_env[index] = NULL;
	return (new_env);
}

int	ft_export(char ***env, char **arg)
{
	char	**new_env;
	char	**old_env;
	int		status;
	int		max;

	status = 0;
	if (*arg)
		*env = ft_delete_var(*env, arg);
	old_env = *env;
	max = ft_max(*env);
	if (!*arg)
	{
		ft_print_sort_env(*env);
		return (status);
	}
	new_env = (char **)malloc(sizeof(char *) * (max + ft_max(arg) + 1));
	if (!new_env)
		error_end(3);
	new_env = ft_env_export(new_env, *env, arg, &status);
	ft_free_env(*env);
	*env = new_env;
	return (status);
}
