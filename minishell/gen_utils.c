/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:54:46 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 01:18:07 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_or_new_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	new->prev = last;
}

void	add_back_or_new_arg(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	last = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_cmd	*init_func(t_var *cntr, t_data *sym)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		error_end(3);
	*new = (t_cmd){};
	new->redir = NULL;
	new->args = NULL;
	cntr->red_c = sym->red_counter;
	cntr->arg_c = sym->args - 1;
	return (new);
}

void	error_end(int flag)
{
	t_malloc_c	*tmp;

	tmp = save_point(NULL, 0);
	clear_point(tmp);
	if (flag == 1)
	{
		printf ("Error: atoi/incorrect argument\n");
		exit (1);
	}
	if (flag == 2)
		printf ("Error: parse error\n");
	if (flag == 3)
	{
		printf ("Error: malloc error\n");
		exit (1);
	}
}

void	fd_init(int fd[2][2], int red_fd[2], t_fd **var, t_cmd *head)
{
	*var = malloc (sizeof(t_fd));
	if (!var)
		error_end(3);
	save_point(*var, 2);
	head = NULL;
	fd[0][0] = -1;
	fd[0][1] = -1;
	fd[1][0] = -1;
	fd[1][1] = -1;
	red_fd[0] = -1;
	red_fd[1] = -1;
	(*var)->error = 0;
	(*var)->i = 0;
}
