/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:45:24 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/20 19:44:51 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_value
{
	int	value;
	int	score_a;
	int	score_b;
	int	flag_rev;
	int	num;
}	t_value;

typedef struct s_stack
{
	t_value	*stack_a;
	t_value	*stack_b;
	int		size_a;
	int		size_b;
	int		flag_all;
	int		flag_ab;
	int		min_score;
	int		min_index;
	int		min_flag;
}	t_stack;

typedef struct s_ops_data
{
	t_value	*stk1;
	t_value	*stk2;
	int		size_to;
	int		size_from;
	int		flag_data;
}	t_ops_data;

typedef struct s_int_data
{
	int	min;
	int	med;
	int	max;
	int	half_med;
	int	min_index;
}	t_int_data;

void		swap(t_stack *stack, int flag);
void		swap_all(t_stack *stack);
void		push(t_stack *stack, int flag);
void		rot(t_stack *stack, int flag);
void		rot_all(t_stack *stack);
void		rev_rot(t_stack *stack, int flag);
void		rev_rot_all(t_stack *stack);

int			sort_eval(t_stack *stack);
void		pushswap_init(t_stack *pushswap, int argc, char **argv);
t_int_data	*med_sort(t_stack *stack, t_int_data *arr_int);
void		presort(t_stack *stack);

void		game_score_init(t_stack *stack);
int			act_option(t_stack *stack, int i);
void		move_elem(t_stack *stack);
void		game_best_way(t_stack *stack);
void		final_rotate(t_stack *stack);

void		game_min_max(t_stack *stack, int flag, int arr_flag);
void		small_sort(t_stack *stack);
void		big_sort(t_stack *stack);

int			ft_atoi(const char *str, t_stack *stack);
void		swap_el(int *a, int *b);
void		error_end(t_stack *stack, int flag);

#endif