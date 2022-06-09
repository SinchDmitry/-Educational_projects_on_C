/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:56:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 06:56:15 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flag_check(t_data **sym, t_cmd *tmp)
{
	if ((*sym)->or && !(*sym)->rm)
		tmp->var_or = 1;
	if ((*sym)->hooks && !(*sym)->rm)
		tmp->sub = 1;
	if ((*sym)->and && !(*sym)->rm)
		tmp->and = 1;
	if ((*sym)->pipe_in_flag && !(*sym)->rm)
		tmp->pipe.in = 1;
	if ((*sym)->pipe_out_flag && !(*sym)->rm)
		tmp->pipe.out = 1;
}

static void	var_work(char tmp, t_env *list_env, t_arg *local)
{
	if (tmp == '$')
	{
		while (list_env)
		{
			if (!ft_strcmp(list_env->key, local->tmp_var))
			{
				local->path = ft_strjoin(local->path, list_env->value);
				break ;
			}
			list_env = list_env->next;
		}
	}
	else
		local->path = ft_strjoin(local->path, local->tmp_var);
}

static void	var_check(t_data **sym, t_cmd *temp, t_arg *local, t_env *list_env)
{
	t_env	*tmp_env;
	char	tmp;

	tmp = (*sym)->prev->sym;
	while ((*sym)->var)
	{
		flag_check(sym, temp);
		local->tmp_var = ft_chrjoin(local->tmp_var, (*sym)->sym);
		if (!(*sym)->next || (*sym)->next->sym == '$' \
			|| space((*sym)->next->sym) || (*sym)->sym == '?')
			break ;
		(*sym) = (*sym)->next;
	}
	tmp_env = list_env;
	var_work(tmp, list_env, local);
	if (!local->path)
		local->path = ft_calloc(1, 1);
	if (local->tmp_var)
		free (local->tmp_var);
}

void	gen_flag_check(t_data **sym, t_cmd *tmp, t_arg *local, char **env)
{
	t_env	*list_env;

	flag_check(sym, tmp);
	if ((*sym)->var && !(*sym)->rm)
	{
		list_env = ft_env_to_list(env);
		local->tmp_var = NULL;
		var_check(sym, tmp, local, list_env);
		kill_env(list_env);
	}
	if (*sym && !(*sym)->rm && !(*sym)->var)
		local->path = ft_chrjoin(local->path, (*sym)->sym);
}

int	break_mod(t_data **sym, t_var c, int mod)
{
	if ((mod == 2 && ((*sym)->args != c.a || (*sym)->red_addr)))
		return (1);
	if (mod == 1 && ((*sym)->red_addr != c.a || (*sym)->red_counter != c.n))
		return (1);
	if ((*sym)->cmd != c.m)
		return (1);
	return (0);
}
