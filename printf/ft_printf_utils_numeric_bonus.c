/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_numeric_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:54:49 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/13 15:44:24 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	pref(t_flag *flag, long long n);
static int	w_d_i_nominus(t_flag *flag, char c, long long a, int len);
static int	w_d_i_minus(t_flag *flag, char c, long long a, int len);
static int	width_dot_input(t_flag *flag, char c, long long a);
int			rd_int(t_flag *flag, int a, char c, int f);

int	rd_int(t_flag *flag, int a, char c, int f)
{
	int				i;
	unsigned int	b;

	i = 0;
	flag->fdiez = 0;
	if (flag->fdot && !(flag->vdot) && a == 0)
	{
		while (i < flag->vwidth)
			i += ft_putchar(c);
		return (i);
	}
	b = (unsigned int)a;
	if (!f)
		i = width_dot_input(flag, c, b);
	else
		i = width_dot_input(flag, c, a);
	return (i);
}

static int	width_dot_input(t_flag *flag, char c, long long a)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	ft_putnbr(a, &len, 0);
	if (flag->fminus)
		i += w_d_i_minus(flag, c, a, len);
	else
		i += w_d_i_nominus(flag, c, a, len);
	return (i);
}

static int	pref(t_flag *flag, long long n)
{
	if (n >= 0)
	{
		if (flag->fplus)
			ft_putchar('+');
		else if (flag->fspace)
			ft_putchar(' ');
		else
			return (0);
	}
	else
	{
		n = -n;
		ft_putchar('-');
	}
	return (1);
}

static int	w_d_i_minus(t_flag *flag, char c, long long a, int len)
{
	int	i;

	i = 0;
	i += pref(flag, a);
	if (flag->fdot)
		while (flag->vdot > len++)
			i += ft_putchar('0');
	ft_putnbr(a, &i, 1);
	while (i < flag->vwidth)
		i += ft_putchar(c);
	return (i);
}

static int	w_d_i_nominus(t_flag *flag, char c, long long a, int len)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = len;
	if (flag->fdot && flag->vdot > len)
		tmp = flag->vdot;
	if (flag->fplus || flag->fspace || (a < 0 && !(flag->fnull)))
		tmp++;
	if (flag->fnull)
		i += pref(flag, a);
	while (i < (flag->vwidth - tmp))
		i += ft_putchar(c);
	if (!flag->fnull)
		i += pref(flag, a);
	if (flag->fdot)
		while (flag->vdot > len++)
			i += ft_putchar('0');
	ft_putnbr(a, &i, 1);
	return (i);
}
