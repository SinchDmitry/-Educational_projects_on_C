/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:49:04 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/10 04:31:55 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *path, char ***g_env)
{
	char	**env;
	int		index;

	index = 0;
	env = *g_env;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	while (env[index] && ft_strncmp("PWD=", env[index], 4))
		++index;
	env[index] = ft_stdstrjoin("PWD=", getcwd(NULL, ft_strlen(path) + 255));
	*g_env = env;
	return (0);
}
