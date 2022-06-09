/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:30:24 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/21 20:09:13 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_sort(t_stack *stack)
{
	t_int_data	small_arr;

	small_arr = *med_sort(stack, &small_arr);
	if (!sort_eval(stack))
		error_end(stack, 4);
	while (stack->size_a > 3)
	{
		if (stack->stack_a[0].value == small_arr.max)
			rot(stack, 1);
		push(stack, 0);
	}
	game_min_max(stack, 0, 0);
	game_min_max(stack, 0, 1);
	while (stack->size_b)
	{
		if (stack->stack_b[0].value < stack->stack_a[0].value)
			push(stack, 1);
		else
			rot(stack, 1);
	}
}

void	big_sort(t_stack *stack)
{
	presort(stack);
	if (!sort_eval(stack))
		error_end(stack, 4);
	game_min_max(stack, 0, 0);
	stack->min_index = 0;
	while (stack->size_b)
	{
		game_score_init(stack);
		game_best_way(stack);
	}
}

static t_value	*array_var(t_stack *stack, int flag)
{
	t_value	*value;

	value = stack->stack_a;
	if (flag)
		value = stack->stack_b;
	return (value);
}

static void	stack_w_three(t_stack *stack, int flag)
{
	t_value	*stack_arr;

	stack_arr = array_var(stack, flag);
	if (stack_arr[0].value > stack_arr[1].value)
	{
		if (stack_arr[1].value > stack_arr[2].value)
		{
			rot(stack, 1);
			swap(stack, 1);
		}
		else if (stack_arr[0].value > stack_arr[2].value)
			rot(stack, 1);
		else
			swap(stack, 1);
	}
	else if (stack_arr[1].value > stack_arr[2].value)
	{
		if (stack_arr[0].value > stack_arr[2].value)
			rev_rot(stack, 1);
		else
		{
			swap(stack, 1);
			rot(stack, 1);
		}
	}
}

void	game_min_max(t_stack *stack, int flag, int arr_flag)
{
	int	size;
	int	el_1;
	int	el_2;

	size = stack->size_a;
	el_1 = stack->stack_a[0].value;
	el_2 = stack->stack_a[1].value;
	if (arr_flag)
	{
		size = stack->size_b;
		el_1 = stack->stack_b[0].value;
		el_2 = stack->stack_b[1].value;
	}
	stack->flag_all = flag;
	if (size == 3)
		stack_w_three(stack, arr_flag);
	if (size == 2)
		if (el_1 > el_2)
			rot(stack, (arr_flag - 1) * (-1));
}
