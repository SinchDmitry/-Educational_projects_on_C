/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:01:09 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/10 01:23:02 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

static void	save_type(t_malloc_c **head, t_malloc_c *new, int flag)
{
	t_malloc_c	*tmp;

	tmp = NULL;
	if (!*head)
		*head = new;
	else if (flag == 2)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (flag == 1)
	{
		new->next = *head;
		*head = new;
	}
}

t_malloc_c	*save_point(void *mal_p, int flag)
{
	static t_malloc_c	*head;
	t_malloc_c			*new;

	if (!flag)
		return (head);
	if (!mal_p)
	{
		head = NULL;
		return (head);
	}
	new = malloc(sizeof(t_malloc_c));
	if (!new)
		error_end(3);
	*new = (t_malloc_c){};
	new->point = mal_p;
	save_type(&head, new, flag);
	return (head);
}

void	clear_point(t_malloc_c *malloc_h)
{
	t_malloc_c	*tmp;

	while (malloc_h)
	{
		tmp = malloc_h->next;
		free(malloc_h->point);
		free(malloc_h);
		malloc_h = tmp;
	}
}
