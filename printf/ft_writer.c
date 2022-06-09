/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:06 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/11 19:21:32 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

void	ft_putnbr(long int n, int *i)
{
	long int	tmp;

	tmp = n;
	(*i)++;
	if (tmp < 0)
	{
		ft_putchar('-');
		(*i)++;
		tmp = -tmp;
	}
	if (tmp / 10)
		ft_putnbr(tmp / 10, i);
	ft_putchar((tmp % 10 + '0'));
}
