/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_start_game.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:54:04 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/20 19:28:58 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	presort(t_stack *stack)
{
	int			a_val;
	t_int_data	a_int;

	a_int = *med_sort(stack, &a_int);
	while (stack->size_a > 3)
	{
		a_val = stack->stack_a[0].value;
		if (a_val != a_int.min && a_val != a_int.max)
		{
			push(stack, 0);
			if (a_val < a_int.med)
				rot(stack, 0);
		}
		else
			rot(stack, 1);
	}
}

static void	game_score_a_check(t_stack *stack, int i)
{
	int	j;

	j = -1;
	stack->stack_b[i].score_a = 0;
	while (++j < stack->size_a)
	{
		if (stack->stack_b[i].value > stack->stack_a[j].value && \
		stack->stack_b[i].value < stack->stack_a[j + 1].value)
		{
			if (j <= stack->size_a / 2)
				stack->stack_b[i].score_a = j + 1;
			else
			{
				stack->stack_b[i].score_a = stack->size_a - (j + 1);
				stack->stack_b[i].flag_rev += 2;
			}
			break ;
		}
	}
}

void	game_score_init(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i < stack->size_b)
	{
		stack->stack_a[i].flag_rev = 0;
		stack->stack_b[i].flag_rev = 0;
		if (i <= stack->size_b / 2)
			stack->stack_b[i].score_b = i;
		else
		{
			stack->stack_b[i].score_b = stack->size_b - i;
			stack->stack_b[i].flag_rev = 1;
		}
		game_score_a_check(stack, i);
	}
}

int	sort_eval(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i < stack->size_a - 1)
		if (stack->stack_a[i].value > stack->stack_a[(i + 1)].value)
			return (1);
	return (0);
}
