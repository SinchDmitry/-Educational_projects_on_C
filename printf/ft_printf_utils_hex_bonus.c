/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_hex_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:54:49 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/13 15:44:01 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void		ft_putnbr(long long n, int *i, int f);
static int	w_d_h_nominus(t_flag *flag, unsigned long int a, char *base, int f);
static int	w_d_h_minus(t_flag *flag, unsigned long int a, char *base, int f);
static int	output_hex(unsigned long int a, char *base, int f);
int			rd_hex(t_flag *flag, long long a, int f);

int	rd_hex(t_flag *flag, long long a, int f)
{
	char	*base;
	int		i;

	i = 0;
	if (flag->fdot && !(flag->vdot) && a == 0)
	{
		while (i < flag->vwidth)
		{
			if (flag->fnull)
				i += ft_putchar('0');
			else
				i += ft_putchar(' ');
		}
		return (i);
	}
	base = "0123456789abcdef";
	if (!f)
		base = "0123456789ABCDEF";
	if (flag->fminus)
		i += w_d_h_minus(flag, a, base, f);
	else
		i += w_d_h_nominus(flag, a, base, f);
	return (i);
}

static int	output_hex(unsigned long int a, char *base, int f)
{
	char				word[19];
	int					i;
	unsigned long int	tmp;

	word[0] = '0';
	i = 0;
	tmp = a;
	if (!a)
		i = 1;
	while (a)
	{
		a = a / 16;
		word[i++] = base[tmp - (a * 16)];
		tmp = a;
	}
	tmp = i;
	if (f)
		while (--i >= 0)
			ft_putchar(word[i]);
	return (tmp);
}

static int	w_d_h_minus(t_flag *flag, unsigned long int a, char *base, int f)
{
	int	i;
	int	len;

	i = 0;
	len = output_hex(a, base, 0);
	if ((flag->fdiez && f == 1 && a) || f == 2)
		i += write (1, "0x", 2);
	if (flag->fdiez && f == 0 && a)
		i += write (1, "0X", 2);
	while (flag->vdot > len++)
		i += ft_putchar('0');
	i += output_hex(a, base, 1);
	while (i < flag->vwidth)
	{
		if (flag->fnull)
			i += ft_putchar('0');
		else
			i += ft_putchar(' ');
	}
	return (i);
}

static int	w_d_h_nominus(t_flag *flag, unsigned long int a, char *base, int f)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = output_hex(a, base, 0);
	if (flag->vdot > tmp)
		tmp = flag->vdot;
	if (f == 2)
		tmp = tmp + 2;
	while (i < (flag->vwidth - tmp))
	{
		if (flag->fnull)
			i += ft_putchar('0');
		else
			i += ft_putchar(' ');
	}
	if ((flag->fdiez && f == 1 && a) || f == 2)
		i += write (1, "0x", 2);
	if (flag->fdiez && f == 0 && a)
		i += write (1, "0X", 2);
	tmp = output_hex(a, base, 0);
	while (flag->vdot > tmp++)
		i += ft_putchar('0');
	i += output_hex(a, base, 1);
	return (i);
}

void	ft_putnbr(long long n, int *i, int f)
{
	long int	tmp;

	tmp = n;
	(*i)++;
	if (tmp < 0)
		tmp = -tmp;
	if (tmp / 10)
		ft_putnbr(tmp / 10, i, f);
	if (f)
		ft_putchar((tmp % 10 + '0'));
}
