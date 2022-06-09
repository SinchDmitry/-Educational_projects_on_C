/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:34:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/07 20:47:13 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*wildcard_init(t_data **sym)
{
	char	*tmp_var;

	tmp_var = NULL;
	while ((*sym)->wild)
	{
		tmp_var = ft_chrjoin(tmp_var, (*sym)->sym);
		(*sym) = (*sym)->next;
		if (!*sym)
			break ;
	}
	return (tmp_var);
}

static void	wildcard_action(t_cmd *tmp, struct dirent *gointo, char *var, int i)
{
	t_arg			*local;

	local = malloc (sizeof(t_arg));
	*local = (t_arg){};
	if (i)
		local->path = ft_strdup(gointo->d_name);
	else
	{
		local->path = ft_strdup(var);
		local->path = ft_chrjoin_f(local->path, '*');
	}
	save_point(local, 1);
	save_point(local->path, 1);
	add_back_or_new_arg(&(tmp->args), local);
}

void	wildcard_add(t_data **sym, t_cmd *tmp)
{
	char			*str;
	char			*var;
	DIR				*mydir;
	struct dirent	*in;
	int				i;

	i = 0;
	str = ft_strdup(getenv("PWD"));
	str = ft_chrjoin(str, '/');
	save_point(str, 2);
	var = wildcard_init(sym);
	save_point(var, 2);
	mydir = opendir(str);
	if (!mydir)
		error_end(3);
	in = readdir(mydir);
	while (in)
	{
		if ((!(ft_strcmp_rev(in->d_name, var)) || !ft_strcmp(var, "*")) && i++)
			wildcard_action(tmp, in, NULL, i);
		in = readdir(mydir);
	}
	if (!i)
		wildcard_action(tmp, in, var, i);
	closedir(mydir);
}
