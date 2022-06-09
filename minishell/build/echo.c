/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:57:55 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/09 22:57:55 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_flag(char *av)
{
	if (*(av++) == '-')
	{
		while (*av == 'n')
			av++;
		if (!*av)
			return (1);
	}
	return (0);
}

int	ft_echo(char **av)
{
	int	flag;

	flag = 0;
	while (*(++av))
	{
		if (!ft_check_flag(*av))
		{
			ft_putstr_fd(*av, 1);
			if (*(av + 1) && !ft_check_flag(*(av + 1)))
				write(1, " ", 1);
		}
		else
			flag = 1;
	}
	if (flag == 0)
		write (1, "\n", 1);
	return (1);
}
