/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_med.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:13:53 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/20 22:25:03 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_el(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	quick(t_stack *stack, int *array, int low, int high)
{
	int	p;
	int	i;
	int	j;

	j = low - 1;
	i = low - 1;
	p = array[high];
	while (++j < high)
	{
		if (array[j] < p)
			swap_el(&array[j], &array[++i]);
		if (array[j] == p)
			error_end(stack, 3);
	}
	swap_el(&array[high], &array[i + 1]);
	return (i + 1);
}

static void	sort(t_stack *stack, int **array, int low, int high)
{
	int	point;

	if (low < high)
	{
		point = quick(stack, *array, low, high);
		sort(stack, array, low, point - 1);
		sort(stack, array, point + 1, high);
	}
}

t_int_data	*med_sort(t_stack *stack, t_int_data *arr_int)
{
	int	i;
	int	*arr;
	int	low;
	int	high;

	i = -1;
	arr = malloc(sizeof(int) * stack->size_a);
	while (++i < stack->size_a)
		arr[i] = stack->stack_a[i].value;
	low = 0;
	high = stack->size_a - 1;
	sort(stack, &arr, low, high);
	arr_int->med = arr[high / 2];
	arr_int->max = arr[high];
	arr_int->min = arr[low];
	arr_int->half_med = arr[high / 4];
	free (arr);
	return (arr_int);
}

void	final_rotate(t_stack *stack)
{
	t_int_data	final;
	int			j;
	int			i_min;

	j = -1;
	final = *med_sort(stack, &final);
	stack->flag_all = 0;
	while (stack->stack_a[++j].value != final.max)
		i_min = j;
	if (j < stack->size_a / 2)
		while (j-- >= 0)
			rot(stack, 1);
	else
		while (++j < stack->size_a)
			rev_rot(stack, 1);
}
