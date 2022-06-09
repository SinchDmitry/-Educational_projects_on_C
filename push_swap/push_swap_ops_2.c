/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:43:07 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/21 20:12:35 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *str, t_stack *stack)
{
	int			i;
	int			a;
	long long	res;

	i = 0;
	a = -1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			a = -a;
	if (str[i] >= 48 && str[i] <= 57)
		while (str[i] >= 48 && str[i] <= 57)
			res = res * 10 - (str[i++] - '0');
	else
		error_end(stack, 3);
	if (a * res > 2147483647 || a * res < -2147483648)
		error_end(stack, 3);
	if (str[i] && str[i] != 32)
		error_end(stack, 3);
	return (a * (int)res);
}

void	rot(t_stack *stack, int flag)
{
	int		i;
	int		size;
	t_value	tmp;
	t_value	*stk;

	if (flag)
	{
		size = stack->size_a;
		stk = stack->stack_a;
		if (!(stack->flag_all))
			write (1, "ra\n", 3);
	}
	else
	{
		size = stack->size_b;
		stk = stack->stack_b;
		if (!(stack->flag_all))
			write (1, "rb\n", 3);
	}
	i = -1;
	tmp = stk[0];
	while (++i < size + 1)
		stk[i] = stk[i + 1];
	stk[size - 1] = tmp;
}

void	rot_all(t_stack *stack)
{
	if (stack->flag_all != 2)
		stack->flag_all = 1;
	rot(stack, 1);
	rot(stack, 0);
	if (stack->flag_all != 2)
		write (1, "rr\n", 3);
	stack->flag_all = 0;
}

void	rev_rot(t_stack *stack, int flag)
{
	int		size;
	t_value	tmp;
	t_value	*stk;

	if (flag)
	{
		size = stack->size_a - 1;
		stk = stack->stack_a;
		if (!(stack->flag_all))
			write (1, "rra\n", 4);
	}
	else
	{
		size = stack->size_b - 1;
		stk = stack->stack_b;
		if (!(stack->flag_all))
			write (1, "rrb\n", 4);
	}
	if (size + 1 > 1)
	{
		tmp = stk[size];
		while (size--)
			stk[size + 1] = stk[size];
		stk[0] = tmp;
	}
}

void	rev_rot_all(t_stack *stack)
{
	if (stack->flag_all != 2)
		stack->flag_all = 1;
	rev_rot(stack, 1);
	rev_rot(stack, 0);
	if (stack->flag_all != 2)
		write (1, "rrr\n", 4);
	stack->flag_all = 0;
}
