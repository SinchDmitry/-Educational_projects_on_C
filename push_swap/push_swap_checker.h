/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_checker.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:24:21 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/20 18:47:58 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_CHECKER_H
# define PUSH_SWAP_CHECKER_H

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

typedef struct s_read
{
	char	c[6];
	char	sym;
	int		i;
	int		byte;
}	t_read;

void		swap(t_stack *stack, int flag);
void		swap_all(t_stack *stack);
void		push(t_stack *stack, int flag);
void		rot(t_stack *stack, int flag);
void		rot_all(t_stack *stack);
void		rev_rot(t_stack *stack, int flag);
void		rev_rot_all(t_stack *stack);

void		pushswap_init(t_stack *pushswap, int argc, char **argv);
int			ft_atoi(const char *str, t_stack *stack);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		error_end(t_stack *stack, int flag);

#endif