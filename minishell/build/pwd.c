/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:07:44 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/10 04:17:30 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **env)
{
	char	*str;

	str = ft_get_env(env, "PWD=");
	if (!str)
		error_end(3);
	printf("%s\n", str);
	return (0);
}
