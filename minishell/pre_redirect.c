/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:32:41 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/06 19:08:57 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	red_part_1(t_data *tmp)
{
	if (tmp->sym == '>' && !tmp->prev->red_first)
	{
		if (tmp->prev->her_first)
			tmp->parse_error = 1;
		tmp->red_first = 1;
		return (0);
	}
	else if (tmp->sym == '<' && !tmp->prev->her_first)
	{
		if (tmp->prev->red_first)
			tmp->parse_error = 1;
		tmp->her_first = 1;
		return (0);
	}
	else if (tmp->sym == '>' && tmp->prev->red_first)
	{
		tmp->red_first = tmp->prev->red_first + 1;
		return (0);
	}
	else if (tmp->sym == '<' && tmp->prev->her_first)
	{
		tmp->her_first = tmp->prev->her_first + 1;
		return (0);
	}
	return (1);
}

static int	red_part_2(t_data *tmp)
{
	if (!(tmp->sym == '>') && tmp->prev->red_first == 1)
	{
		tmp->redir = 2;
		tmp->red_first = 0;
	}	
	else if (!(tmp->sym == '>') && tmp->prev->red_first == 2)
	{
		tmp->redir = 4;
		tmp->red_first = 0;
	}	
	else if (!(tmp->sym == '<') && tmp->prev->her_first == 1)
	{
		tmp->redir = 1;
		tmp->her_first = 0;
	}	
	else if (!(tmp->sym == '<') && tmp->prev->her_first == 2)
	{
		tmp->redir = 3;
		tmp->her_first = 0;
	}
	else
		return (1);
	tmp->red_addr = tmp->args + 1;
	tmp->red_counter++;
	return (0);
}

static void	red_error(t_data *tmp)
{
	t_data	*prv;

	prv = tmp->prev;
	while (prv->rm == 1 || prv->rm == 2)
		prv = prv->prev;
	if ((tmp->sym == '>' || tmp->sym == '<') && \
		(prv->sym == '>' || prv->sym == '<') && \
		(!tmp->prev->her_first && !tmp->prev->red_first))
		tmp->parse_error = 1;
	if ((tmp->sym == '>' || tmp->sym == '<') && \
		(tmp->red_addr && !tmp->prev->rm))
		tmp->parse_error = 1;
}

void	red_check(t_data *tmp)
{
	red_error(tmp);
	if (!red_part_1(tmp))
		return ;
	else if (!red_part_2(tmp))
		return ;
	if (tmp->prev->her_first > 2 || tmp->prev->red_first > 2)
		tmp->parse_error = 1;
	else
	{
		tmp->her_first = 0;
		tmp->red_first = 0;
	}
}

void	red_addr_check(t_data *tmp)
{
	if (tmp->red_addr && (tmp->args >= tmp->red_addr))
	{
		if (space(tmp->prev->sym))
		{
			tmp->red_addr = 0;
			tmp->redir = 0;
		}
	}
	if (tmp->red_addr && ((tmp->args < tmp->red_addr - 1 && \
		(tmp->sym == '<' || tmp->sym == '>')) || tmp->wild))
		tmp->parse_error = 1;
}
