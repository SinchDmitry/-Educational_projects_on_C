/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_char_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:43:55 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/13 15:43:55 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int			ft_putchar(char c);
static int	w_d_ch_nominus(t_flag *flag, char *c);
static int	w_d_ch_minus(t_flag *flag, char *c);
int			d_str(t_flag *flag, char *c);
int			rd_ch(t_flag *flag, char c);

int	rd_ch(t_flag *flag, char c)
{
	int	i;

	i = 0;
	if (!(flag->fwidth) && ++i)
		ft_putchar(c);
	else
	{
		if (flag->fminus)
		{
			i += ft_putchar(c);
			while (i < flag->vwidth)
				i += ft_putchar(' ');
		}
		else
		{
			while (i < flag->vwidth - 1)
				i += ft_putchar(' ');
			i += ft_putchar(c);
		}
	}
	return (i);
}

int	rd_str(t_flag *flag, char *c)
{
	int	i;

	i = 0;
	if (!c)
		c = "(null)";
	if (flag->fminus)
		i = w_d_ch_minus(flag, c);
	else
		i = w_d_ch_nominus(flag, c);
	return (i);
}

static int	w_d_ch_minus(t_flag *flag, char *c)
{
	int	tmp;
	int	i;

	tmp = ft_strlen(c);
	i = 0;
	if (flag->fdot)
		if ((flag->vdot) < tmp)
			tmp = flag->vdot;
	while (i < tmp)
		i += ft_putchar(c[i]);
	while (i < flag->vwidth)
		i += ft_putchar(' ');
	return (i);
}

static int	w_d_ch_nominus(t_flag *flag, char *c)
{		
	int	tmp;
	int	i;
	int	a;

	tmp = ft_strlen(c);
	i = 0;
	a = 0;
	if (flag->fdot)
		if ((flag->vdot) < tmp)
			tmp = flag->vdot;
	if (flag->vwidth > tmp)
	{
		while (i < (flag->vwidth - tmp))
			i += ft_putchar(' ');
		tmp = flag->vwidth;
	}
	while (i < tmp)
		i += ft_putchar(c[a++]);
	return (i);
}

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}
