/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:31:33 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 01:33:23 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pars(char *str)
{
	if ((*str < 'a' || *str > 'z') && (*str < 'A' || *str > 'Z'))
		return (0);
	while (*str && *str != '=')
	{
		if ((*str < 'a' || *str > 'z') && \
		(*str < '0' || *str > '9') && (*str < 'A' || *str > 'Z'))
			return (0);
		++str;
	}
	return (1);
}

int	ft_check_sort(char **env)
{
	while (*env && env[1])
	{
		if (ft_strcmp(*env, env[1]) > 0)
			return (0);
		else if (*env)
			++env;
	}
	return (1);
}

int	ft_max(char **env)
{
	int	index;

	index = 0;
	while (env[index])
		++index;
	return (index);
}

int	ft_check_double(char *str, char **arg)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		++size;
	while (*arg)
	{
		if (!ft_strncmp(str, *arg, size))
			return (1);
		++arg;
	}
	return (0);
}

int	ft_check_eq(char *str)
{
	while (*str)
	{
		if (*(str++) == '=')
			return (1);
	}
	return (0);
}
