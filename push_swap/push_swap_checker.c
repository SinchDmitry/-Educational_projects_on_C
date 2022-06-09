/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:44:06 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/21 20:08:41 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_checker.h"

static void	checker_action(t_stack *stack, char *c)
{
	stack->flag_all = 2;
	if (!(ft_strncmp(c, "sa", 2)))
		swap(stack, 1);
	else if (!(ft_strncmp(c, "sb", 2)))
		swap(stack, 0);
	else if (!(ft_strncmp(c, "ss", 2)))
		swap_all(stack);
	else if (!(ft_strncmp(c, "pa", 2)))
		push(stack, 1);
	else if (!(ft_strncmp(c, "pb", 2)))
		push(stack, 0);
	else if (!(ft_strncmp(c, "rrr", 3)))
		rev_rot_all(stack);
	else if (!(ft_strncmp(c, "ra", 2)))
		rot(stack, 1);
	else if (!(ft_strncmp(c, "rb", 2)))
		rot(stack, 0);
	else if (!(ft_strncmp(c, "rra", 3)))
		rev_rot(stack, 1);
	else if (!(ft_strncmp(c, "rrb", 3)))
		rev_rot(stack, 0);
	else if (!(ft_strncmp(c, "rr", 2)))
		rot_all(stack);
	else if (*c)
		error_end(stack, 3);
}

static void	checker_eval(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i < stack->size_a - 1)
	{
		if (stack->stack_a[i].value > stack->stack_a[(i + 1)].value)
		{
			write (1, "KO", 2);
			return ;
		}
	}
	write (1, "OK", 2);
}

void	pushswap_init(t_stack *pushswap, int argc, char **argv)
{
	int		i;

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

void	error_end(t_stack *stack, int flag)
{
	if (!flag)
		write(1, "bad arguments\n", 14);
	else if (flag == -1)
		write(1, "Error\n", 6);
	else
	{
		free(stack->stack_a);
		if (flag == 1)
			write(1, "bad character\n", 14);
		else if (flag == 2)
			write(1, "malloc error\n", 13);
		else if (flag == 3)
			write(1, "Error\n", 6);
		else if (flag == 4)
			flag = 4;
	}
	exit (1);
}

int	main(int argc, char **argv)
{
	t_stack	checkswap;
	t_read	info;

	if (argc < 2)
		error_end(&checkswap, -1);
	pushswap_init(&checkswap, argc, argv);
	info.byte = 1;
	while (info.byte)
	{
		info.i = 0;
		while (1)
		{
			info.byte = read(0, &info.sym, 1);
			if (!info.byte || info.sym == '\n')
				break ;
			if (info.byte < 0 && info.i > 4)
				error_end(&checkswap, 3);
			info.c[info.i++] = info.sym;
		}
		info.c[info.i] = 0;
		checker_action(&checkswap, info.c);
	}
	checker_eval(&checkswap);
	return (0);
}
