/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:45:24 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/13 15:46:13 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_flag
{
	int	fnull;
	int	fspace;
	int	fdiez;
	int	fminus;
	int	fplus;
	int	fdot;
	int	vdot;	
	int	fwidth;
	int	vwidth;
}	t_flag;

int		rd_int(t_flag *flag, int a, char c, int f);
int		rd_hex(t_flag *flag, long long a, int f);
int		rd_ch(t_flag *flag, char c);
int		rd_str(t_flag *flag, char *c);

void	ft_putnbr(long long n, int *i, int f);
int		ft_putchar(char c);

t_flag	*ft_null(t_flag *f);
t_flag	*flaginit(t_flag *f, const char *str, int *i);

int		flag_type(int a, va_list param, char c, t_flag *f);
int		find_chr(int f, int c);
int		ft_printf(const char *str, ...);

#endif