/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:42:31 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 03:41:07 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_init(t_data *tmp, t_var *q_var, int num_quote)
{
	q_var->temp_prev = NULL;
	q_var->q_ch = '\'';
	if (tmp->prev)
		q_var->temp_prev = &tmp->prev->once_q;
	q_var->temp = &tmp->once_q;
	if (num_quote == 2)
	{
		q_var->q_ch = '"';
		if (tmp->prev)
			q_var->temp_prev = &tmp->prev->double_q;
		q_var->temp = &tmp->double_q;
	}
}

void	hooks_check(t_data *tmp)
{
	t_data	*prv;

	prv = tmp->prev;
	while (prv && (prv->rm == 1 || prv->rm == 2))
		if (prv)
			prv = prv->prev;
	if (tmp->sym == ')')
	{
		if (tmp->hooks % 2 != 0)
		{
			tmp->rm = 5;
			tmp->hooks = 0;
		}
		else
			tmp->parse_error = 1;
	}
	else if (tmp->hooks % 2 == 0 && tmp->sym == '(')
	{
		if (iscmd(prv->sym) || prv->sym == '(')
		{
			tmp->rm = 5;
			tmp->hooks = 1;
		}
	}
}

void	quote_check(t_data *tmp, int num_quote)
{
	t_var	q_var;

	quote_init(tmp, &q_var, num_quote);
	if (tmp->sym == q_var.q_ch)
	{
		tmp->rm = 2;
		*q_var.temp = *q_var.temp_prev + 1;
		if ((*q_var.temp % 2) && tmp->prev)
		{
			if (tmp->prev->rm == 1 || iscmd(tmp->prev->sym))
				tmp->args++;
		}
	}
	if (tmp->sym == '$' && !(tmp->once_q % 2) && tmp->redir != 3 \
		&& !tmp->wild)
	{
		tmp->var = 1;
		tmp->rm = 4;
	}
}

void	arg_check(t_data *tmp)
{
	t_data	*prv;

	prv = tmp->prev;
	while (prv->prev && (prv->rm == 1 || prv->rm == 2))
		prv = prv->prev;
	if ((!space(tmp->sym) && !iscmd(tmp->sym)) && (!iscmd(prv->sym) \
	&& tmp->prev->rm == 1))
	{
		tmp->wild = 0;
		tmp->args++;
	}
	if (tmp->sym == '*' && (space(tmp->prev->sym) || tmp->prev->sym == '*'))
	{
		tmp->wild = 1;
		tmp->rm = 2;
	}
	if (!space(tmp->sym) && !iscmd(tmp->sym) && prv->sym == ')')
	{
		tmp->parse_error = 1;
		tmp->wild = 0;
	}
	red_addr_check(tmp);
}

void	rm_check(t_data *tmp)
{
	if (tmp->sym == '$' && !(tmp->once_q % 2) && tmp->redir != 3 && !tmp->wild)
	{
		tmp->var = 1;
		tmp->rm = 4;
	}
	if (space(tmp->sym))
	{
		tmp->var = 0;
		tmp->rm = 1;
	}
	if (tmp->sym == '\'' && !(tmp->double_q % 2))
	{
		tmp->var = 0;
		tmp->rm = 2;
	}
	if (tmp->sym == '"' && !(tmp->once_q % 2))
	{
		tmp->var = 0;
		tmp->rm = 2;
	}
	if (iscmd(tmp->sym))
	{
		tmp->var = 0;
		tmp->rm = 3;
	}
}
