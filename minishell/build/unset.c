/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:33:44 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 01:34:57 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_arg(char *str, char **arg)
{
	char	*check;
	int		index;

	index = 0;
	check = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!check)
		return (-1);
	while (*str != '=' && *str)
		check[index++] = *(str++);
	check[index] = '\0';
	while (*arg)
	{
		if (!ft_strcmp(*arg, check) && !ft_check_eq(*arg))
		{
			free(check);
			return (1);
		}
		++arg;
	}
	free(check);
	return (0);
}

int	ft_pars_unset(char **arg, int flag)
{
	int	error_index;

	error_index = 0;
	while (*arg)
	{
		if (!ft_pars(*arg) || ft_check_eq(*arg))
		{
			++error_index;
			if (flag)
			{
				ft_putstr_fd("minishell: unset: ", 2);
				ft_putstr_fd(*arg, 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
			}
		}
		++arg;
	}
	return (error_index);
}

int	ft_unset(char ***env, char **arg, int flag)
{
	char	**new_env;
	int		max;
	int		index;
	int		env_index;

	env_index = 0;
	if (!*arg)
		return (0);
	index = 0;
	max = ft_max(*env);
	new_env = (char **)malloc(sizeof(char *) * (max + 2));
	if (!new_env)
		return (1);
	ft_pars_unset(arg, flag);
	while ((*env)[env_index])
	{
		if ((*env)[env_index] && !ft_check_arg((*env)[env_index], arg))
			new_env[index++] = ft_strdup((*env)[env_index]);
		env_index++;
	}
	if (flag)
		ft_free_env(*env);
	new_env[index] = NULL;
	*env = new_env;
	return (0);
}
