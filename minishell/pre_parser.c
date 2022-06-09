/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:24 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/07 21:10:52 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*pre_parse_it(char sym, t_data *prev)
{
	t_data	*tmp;

	tmp = malloc(sizeof(t_data));
	if (!tmp)
		error_end(3);
	*tmp = (t_data){};
	tmp->sym = sym;
	tmp->prev = prev;
	if (tmp->prev)
	{
		re_init(tmp);
		pre_check(tmp);
	}
	else
		pre_check_first(tmp);
	return (tmp);
}

static void	last_check(t_data *tmp)
{
	t_data	*prv;

	prv = tmp->prev;
	while (prv && (prv->rm == 1 || prv->rm == 2))
		if (prv)
			prv = prv->prev;
	if ((tmp->sym == '>' || tmp->sym == '<'))
		tmp->parse_error = 1;
	else if (space(tmp->sym))
		if (prv && (prv->sym == '>' || prv->sym == '<'))
			tmp->parse_error = 1;
	if ((tmp->sym != '\'' || tmp->sym != '"') && \
		((tmp->double_q % 2) || (tmp->once_q % 2)))
		tmp->parse_error = 1;
	if (tmp->hooks % 2 || iscmd(tmp->sym))
		tmp->parse_error = 1;
	if (prv && (space(tmp->sym) && iscmd(prv->sym)))
		tmp->parse_error = 1;
}

static	void	rm_sym_check(t_data	*preparse)
{
	t_data	*tmp;
	int		i;

	tmp = preparse;
	i = 0;
	while (tmp)
	{
		if (!tmp->rm)
			i++;
		tmp = tmp->next;
	}
	if (!i && preparse)
	{
		preparse->rm = 0;
		preparse->var = 0;
		preparse->next = NULL;
	}
}

t_data	*sym_parse(char *str)
{
	int		i;
	t_data	*preparse;
	t_data	*tmp;
	t_data	*tmp_old;

	i = -1;
	preparse = NULL;
	tmp_old = NULL;
	while (str[++i])
	{
		tmp = pre_parse_it(str[i], tmp_old);
		if (!str[i + 1])
			last_check(tmp);
		save_point(tmp, 2);
		add_back_or_new(&preparse, tmp);
		if (tmp->parse_error == 1)
			preparse->parse_error = 1;
		tmp_old = tmp;
	}
	rm_sym_check(preparse);
	return (preparse);
}
