/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:34:24 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/20 19:26:06 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *stack, int flag)
{
	t_value	tmp;
	t_value	*stk;
	int		size;

	if (flag)
	{
		size = stack->size_a;
		stk = stack->stack_a;
		if (!(stack->flag_all))
			write (1, "sa\n", 3);
	}
	else
	{
		size = stack->size_b;
		stk = stack->stack_b;
		if (!(stack->flag_all))
			write (1, "sb\n", 3);
	}
	if (size > 1)
	{
		tmp = stk[0];
		stk[0] = stk[1];
		stk[1] = tmp;
	}
}

void	swap_all(t_stack *stack)
{
	if (stack->flag_all != 2)
		stack->flag_all = 1;
	swap(stack, 1);
	swap(stack, 0);
	if (stack->flag_all != 2)
		write (1, "ss\n", 3);
	stack->flag_all = 0;
}

static void	push_init(t_stack *stack, t_ops_data *push)
{
	if (push->flag_data)
	{
		push->stk1 = stack->stack_a;
		push->stk2 = stack->stack_b;
		if (stack->size_b)
		{
			push->size_to = (stack->size_a)++;
			push->size_from = (stack->size_b)--;
		}
		if (!(stack->flag_all))
			write (1, "pa\n", 3);
	}
	else
	{
		push->stk1 = stack->stack_b;
		push->stk2 = stack->stack_a;
		if (stack->size_a)
		{
			push->size_to = (stack->size_b)++;
			push->size_from = (stack->size_a)--;
		}
		if (!(stack->flag_all))
			write (1, "pb\n", 3);
	}
}

void	push(t_stack *stack, int flag)
{	
	t_ops_data	push;
	int			i;

	push.size_to = 0;
	push.size_from = 0;
	push.flag_data = flag;
	push_init(stack, &push);
	i = push.size_to;
	if (push.size_from)
	{
		if (push.size_to)
			while (i--)
				push.stk1[i + 1] = push.stk1[i];
		push.stk1[0] = push.stk2[0];
		while (++i < push.size_from)
			push.stk2[i - 1] = push.stk2[i];
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n && (tmps1[i] || tmps2[i]))
	{
		if (tmps1[i] != tmps2[i])
			return (tmps1[i] - tmps2[i]);
		i++;
	}
	return (0);
}
