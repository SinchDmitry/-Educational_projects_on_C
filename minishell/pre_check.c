/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:11:19 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 06:39:38 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_check_first(t_data *tmp)
{
	if (iscmd(tmp->sym) || tmp->sym == ')')
		tmp->parse_error = 1;
	if (tmp->sym == '\'')
		tmp->once_q++;
	if (tmp->sym == '"')
		tmp->double_q++;
	if (tmp->sym == '"' || tmp->sym == '\'')
		tmp->rm = 2;
	if (tmp->sym == '(')
	{
		tmp->hooks++;
		tmp->rm = 5;
	}
	if (tmp->sym == '*')
	{
		tmp->wild = 1;
		tmp->rm = 2;
	}
	if (tmp->sym == '$' && !tmp->wild)
	{
		tmp->var = 1;
		tmp->rm = 4;
	}
	if (space(tmp->sym))
		tmp->rm = 1;
}

void	pre_check(t_data *tmp)
{
	if (!(tmp->double_q % 2))
		quote_check(tmp, 1);
	if (!(tmp->once_q % 2))
		quote_check(tmp, 2);
	hooks_check(tmp);
	if (!(tmp->double_q % 2) && !(tmp->once_q % 2) && !(tmp->hooks % 2))
	{
		if (iscmd(tmp->sym) || iscmd(tmp->prev->sym))
		{
			and_check(tmp);
			or_check(tmp);
			cmd_check(tmp);
			red_check(tmp);
		}
		arg_check(tmp);
		rm_check(tmp);
	}
}
