/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:51:38 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/21 20:13:48 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_end(t_stack *stack, int flag)
{
	if (!flag)
		write(1, "bad arguments\n", 14);
	else if (flag == -1)
		write(1, "Error\n", 6);
	else if (flag == -2)
		exit (1);
	else
	{
		free(stack->stack_a);
		if (flag == 1)
			write(1, "bad character\n", 14);
		else if (flag == 2)
			write(1, "malloc error\n", 13);
		else if (flag == 3)
			write(1, "Error\n", 6);
	}
	exit (1);
}

void	pushswap_init(t_stack *pushswap, int argc, char **argv)
{
	int	i;

	i = -1;
	pushswap->stack_a = malloc (sizeof (t_value) * (argc - 1) * 2);
	if (!pushswap->stack_a)
		error_end(pushswap, 2);
	pushswap->stack_b = pushswap->stack_a + argc;
	while (++i < argc - 1)
		pushswap->stack_a[i].value = ft_atoi(argv[i + 1], pushswap);
	pushswap->size_a = (argc - 1);
	pushswap->size_b = 0;
	pushswap->flag_all = 0;
	pushswap->flag_ab = 0;
	pushswap->min_flag = -1;
	pushswap->min_index = -1;
	pushswap->min_score = -1;
}

void	game_best_way(t_stack *stack)
{
	int	i;
	int	score;

	i = -1;
	score = 0;
	stack->min_score = stack->size_a + stack->size_b;
	while (++i < stack->size_b)
	{
		if (stack->stack_b[i].flag_rev != 1 && stack->stack_b[i].flag_rev != 2)
		{
			if (stack->stack_b[i].score_b >= stack->stack_b[i].score_a)
				score = stack->stack_b[i].score_b;
			else
				score = stack->stack_b[i].score_a;
		}
		else
			score = act_option(stack, i);
		if (score < stack->min_score)
		{
			stack->min_score = score;
			stack->min_index = i;
			stack->min_flag = stack->stack_b[i].flag_rev;
		}
	}
	move_elem(stack);
}

int	main(int argc, char **argv)
{
	t_stack		pushswap;

	if (argc < 2)
		error_end(&pushswap, -2);
	pushswap_init(&pushswap, argc, argv);
	if (argc > 6)
		big_sort(&pushswap);
	else
		small_sort(&pushswap);
	final_rotate(&pushswap);
	free (pushswap.stack_a);
	return (0);
}
