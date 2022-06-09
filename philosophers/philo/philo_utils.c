/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:49 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/09 00:05:48 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_args	*args_init(int argc, char **argv)
{
	t_args	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof (t_args));
	if (!tmp)
		return (NULL);
	while (++i < argc)
		if (ft_atoi(argv[i]) <= 0)
			return (NULL);
	*tmp = (t_args){};
	tmp->number_of_philo = ft_atoi(argv[1]);
	tmp->time_to_die = ft_atoi(argv[2]);
	tmp->time_to_eat = ft_atoi(argv[3]);
	tmp->time_to_sleep = ft_atoi(argv[4]);
	tmp->number_of_eat = -1;
	if (argc == 6)
		tmp->number_of_eat = ft_atoi(argv[5]);
	return (tmp);
}

void	ph_writer(t_philo *ph, t_args *data, int flag)
{
	long	act_ti;

	act_ti = cur_ti() - data->st_t;
	pthread_mutex_lock(&ph->in_data->write);
	ft_putnbr(act_ti);
	write(1, " ", 1);
	ft_putnbr(ph->id);
	if (flag == 11)
		write(1, " has taken a fork\n", 18);
	if (flag == 12)
		write(1, " is eating\n", 11);
	if (flag == 13)
		write(1, " is sleeping\n", 13);
	if (flag == 14)
		write(1, " is thinking\n", 13);
	pthread_mutex_unlock(&(ph->in_data->write));
}
