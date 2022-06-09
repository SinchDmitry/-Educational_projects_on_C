/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:49 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/09 20:29:11 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		a;
	long	res;

	i = 0;
	a = -1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			a = -a;
	while (str[i] == '0')
		i++;
	if (str[i] >= 48 && str[i] <= 57)
	{
		while (str[i] >= 48 && str[i] <= 57)
			res = res * 10 - (str[i++] - '0');
		if (str[i])
			return (-1);
	}
	else
		return (-1);
	return (a * (int)res);
}

long	cur_ti(void)
{
	struct timeval	time;
	long			value;

	gettimeofday(&time, NULL);
	value = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (value);
}

void	ft_usleep(int mtime)
{
	long		start;

	start = cur_ti();
	usleep(mtime * 950);
	while ((mtime + start) > cur_ti())
		usleep(250);
}

void	ph_writer(t_args *data, int flag)
{
	long	act_ti;

	act_ti = cur_ti() - data->st_t;
	sem_wait(data->write);
	ft_putnbr(act_ti);
	write(1, " ", 1);
	ft_putnbr(data->counter);
	if (flag == 11)
		write(1, " has taken a fork\n", 18);
	if (flag == 12)
		write(1, " is eating\n", 11);
	if (flag == 13)
		write(1, " is sleeping\n", 13);
	if (flag == 14)
		write(1, " is thinking\n", 13);
	sem_post(data->write);
}

void	ft_putnbr(int n)
{
	long	tmp;
	long	num;

	tmp = n;
	if (tmp < 0)
	{
		write(1, "-", 1);
		tmp = -tmp;
	}
	if (tmp / 10)
		ft_putnbr(tmp / 10);
	num = (tmp % 10 + '0');
	write(1, &num, 1);
}
