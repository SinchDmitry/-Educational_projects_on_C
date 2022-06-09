/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:58:38 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/19 22:40:20 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	act_param(t_stack *stack, t_stack *v, int i)
{
	v->stack_a[0].value = stack->stack_b[i].score_b + stack->stack_b[i].score_a;
	v->stack_a[0].flag_rev = stack->stack_b[i].flag_rev;
	v->stack_a[0].num = 0;
	if (stack->stack_b[i].flag_rev == 1)
		v->stack_a[1].flag_rev = 3;
	else if (stack->stack_b[i].flag_rev == 2)
		v->stack_a[1].flag_rev = 0;
	if (stack->stack_b[i].score_b > stack->size_a - stack->stack_b[i].score_a)
		v->stack_a[1].value = stack->stack_b[i].score_b;
	else
		v->stack_a[1].value = stack->size_a - stack->stack_b[i].score_a;
	v->stack_a[1].num = 1;
	if (stack->stack_b[i].flag_rev == 1)
		v->stack_a[2].flag_rev = 0;
	else if (stack->stack_b[i].flag_rev == 2)
		v->stack_a[2].flag_rev = 3;
	if (stack->size_b - stack->stack_b[i].score_b > stack->stack_b[i].score_a)
		v->stack_a[2].value = stack->size_b - stack->stack_b[i].score_b;
	else
		v->stack_a[2].value = stack->stack_b[i].score_a;
	v->stack_a[2].num = 2;
}

static void	both_rotate_stacks(t_stack *stack, int both, int end)
{
	int	j;
	int	flag_rev;

	j = -1;
	flag_rev = stack->stack_b[stack->min_index].flag_rev;
	while (++j < both)
	{
		if (flag_rev == 0)
			rot_all(stack);
		else if (flag_rev == 3)
			rev_rot_all(stack);
	}
	while (j++ < end)
	{
		if (flag_rev == 0)
			rot(stack, stack->flag_ab);
		else if (flag_rev == 3)
			rev_rot(stack, stack->flag_ab);
	}
}

static void	otherside_rotate_stacks(t_stack *stack)
{
	int	j;
	int	r_up;
	int	r_down;
	int	flag_rev;

	j = -1;
	flag_rev = stack->stack_b[stack->min_index].flag_rev;
	r_up = stack->stack_b[stack->min_index].score_a;
	r_down = stack->stack_b[stack->min_index].score_b;
	if (flag_rev == 2)
	{
		r_up = stack->stack_b[stack->min_index].score_b;
		r_down = stack->stack_b[stack->min_index].score_a;
	}
	while (++j < r_up)
		rot(stack, (flag_rev % 2));
	j = -1;
	while (++j < r_down)
		rev_rot(stack, (flag_rev + 1) % 2);
}

int	act_option(t_stack *stack, int i)
{
	t_stack	v;

	v.stack_a = malloc (sizeof(t_value) * 4);
	v.size_a = 3;
	act_param(stack, &v, i);
	game_min_max(&v, 1, 0);
	if (v.stack_a[0].num == 1)
		stack->stack_b[i].score_a = stack->size_a - stack->stack_b[i].score_a;
	else if (v.stack_a[0].num == 2)
		stack->stack_b[i].score_b = stack->size_b - stack->stack_b[i].score_b;
	stack->stack_b[i].flag_rev = v.stack_a[0].flag_rev;
	i = v.stack_a[0].value;
	free (v.stack_a);
	return (i);
}

void	move_elem(t_stack *stack)
{
	int	r_both;
	int	r_end;

	if (stack->stack_b[stack->min_index].flag_rev == 1 || \
		stack->stack_b[stack->min_index].flag_rev == 2)
		otherside_rotate_stacks(stack);
	else if (stack->stack_b[stack->min_index].flag_rev == 0 || \
		stack->stack_b[stack->min_index].flag_rev == 3)
	{
		r_both = stack->stack_b[stack->min_index].score_a;
		r_end = stack->stack_b[stack->min_index].score_b;
		stack->flag_ab = 0;
		if (stack->stack_b[stack->min_index].score_b <= \
			stack->stack_b[stack->min_index].score_a)
		{
			r_both = stack->stack_b[stack->min_index].score_b;
			r_end = stack->stack_b[stack->min_index].score_a;
			stack->flag_ab = 1;
		}
		both_rotate_stacks(stack, r_both, r_end);
	}
	push(stack, 1);
}
