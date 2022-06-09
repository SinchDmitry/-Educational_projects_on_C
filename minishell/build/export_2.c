/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 02:46:43 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/10 07:27:35 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_exp_utils(char **arg, int *status, int *index, char **new_env)
{
	if (!ft_pars(*arg))
	{
		*status = 1;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(*arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (new_env);
	}
	if (ft_check_eq(*arg) && !ft_check_double(*arg, arg + 1))
	{
		new_env[(*index)++] = ft_strdup(*arg);
		if (!new_env[*index - 1])
			error_end(3);
	}
	return (new_env);
}

char	**ft_new_arg(char **arg, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(arg[i]) + 1));
		if (!tmp[i])
			error_end(3);
		while (arg[i][j] && arg[i][j] != '=')
		{	
			tmp[i][j] = arg[i][j];
			++j;
		}
		tmp[i][j] = 0;
		++i;
	}
	tmp[i] = NULL;
	return (tmp);
}
