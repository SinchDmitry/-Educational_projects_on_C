/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:56:35 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 06:56:41 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*combine(t_data **sym, char **env, int *counter)
{
	t_cmd	*new;
	t_var	cntr;

	new = init_func(&cntr, *sym);
	while (*sym)
	{
		if ((*sym)->cmd != *counter)
			break ;
		gen_check(sym, new, &cntr, env);
	}
	(*counter)++;
	return (new);
}

char	**conv_to_str(t_arg *args)
{
	int		i;
	char	**arg;
	t_arg	*tmp;

	i = 0;
	tmp = args;
	while (tmp && i++ >= 0)
		tmp = tmp->next;
	tmp = args;
	arg = malloc (sizeof(char *) * (i + 2));
	if (!arg)
		error_end(3);
	save_point(arg, 2);
	i = 0;
	while (tmp)
	{
		arg[i++] = tmp->path;
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}

void	gen_check(t_data **sym, t_cmd *tmp, t_var *cntr, char **env)
{
	t_arg	*arg;
	t_arg	*redir;

	if ((*sym)->red_counter != cntr->red_c && (*sym)->red_addr)
	{
		redir = gen_arg_check(sym, tmp, env, 1);
		save_point(redir, 1);
		save_point(redir->path, 1);
		add_back_or_new_arg(&tmp->redir, redir);
	}
	else if ((*sym)->args != cntr->arg_c && !(*sym)->rm)
	{
		if ((*sym)->wild && !(*sym)->rm)
			wildcard_add(sym, tmp);
		else
		{
			arg = gen_arg_check(sym, tmp, env, 2);
			save_point(arg, 1);
			save_point(arg->path, 1);
			add_back_or_new_arg(&tmp->args, arg);
		}
	}
	else
		(*sym) = (*sym)->next;
}

t_arg	*gen_arg_check(t_data **sym, t_cmd *tmp, char **env, int mod)
{
	t_var	c;
	t_arg	*local;

	c.a = (*sym)->red_addr;
	c.n = (*sym)->red_counter;
	c.m = (*sym)->cmd;
	if (mod == 2)
		c.a = (*sym)->args;
	local = malloc(sizeof(t_arg));
	if (!local)
		error_end(3);
	*local = (t_arg){};
	if (mod == 1)
		local->type = (*sym)->redir;
	while (*sym)
	{
		if (break_mod(sym, c, mod) == 1)
			break ;
		gen_flag_check(sym, tmp, local, env);
		if (*sym)
			*sym = (*sym)->next;
	}
	local->path = ft_strtrim(local->path, " ");
	return (local);
}

t_cmd	*cmd_parse(t_cmd *tmp, t_data *sym, char ***env)
{
	t_cmd	*head_tmp;
	t_cmd	*old_tmp;
	t_fd	*var;
	int		fd[2][2];
	int		red_fd[2];

	head_tmp = NULL;
	fd_init(fd, red_fd, &var, head_tmp);
	old_tmp = NULL;
	while (sym)
	{
		tmp = combine(&sym, *env, &var->i);
		save_point(tmp, 2);
		add_back_or_new_cmd(&head_tmp, tmp);
		tmp->argum = conv_to_str(tmp->args);
		if (tmp->var_or == 1 && var->error == 0)
			return (head_tmp);
		if (tmp->var_or == 1)
			var->error = 0;
		if (var->error == 0)
			if (!minishell(tmp, env, fd, red_fd))
				var->error = 1;
		old_tmp = tmp;
	}
	return (head_tmp);
}
