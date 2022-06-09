/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:47 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/09 00:02:59 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_exit(t_args *data, int flag)
{	
	if (flag < 0)
	{
		free(data);
		flag *= -1;
	}
	if (flag == 100)
		write(2, "Error: wrong number of arguments\n", 33);
	if (flag == 101)
		write(2, "Error: incorrect arguments\n", 27);
	if (flag == 102)
		write(2, "Error: memory error\n", 20);
	return (1);
}

int	analisys(t_philo *ph, int i)
{
	while (++i < ph->in_data->number_of_philo)
	{
		if (ph->in_data->number_of_philo == ph->in_data->eat_counter)
		{
			pthread_mutex_lock(&ph->in_data->write);
			printf("All %d iter has ended\n", ph->in_data->eat_counter);
			return (1);
		}
		if (!ph[i].finish_act)
		{	
			if ((cur_ti() - ph[i].st_eat) > (ph->in_data->time_to_die))
			{
				pthread_mutex_lock(&ph->in_data->write);
				printf("%ld %d died\n", cur_ti() - ph->in_data->st_t, ph->id);
				return (1);
			}
		}
		usleep(1000);
	}
	return (0);
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

void	*inspect(void *philo)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		i = -1;
		if (analisys(ph, i))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_args		*data;
	t_philo		*philo;
	pthread_t	*threads;

	if (argc > 6 || argc < 5)
		return (err_exit(NULL, ARG_ERR));
	data = args_init(argc, argv);
	if (!data)
		return (err_exit(NULL, PARSE_ERR));
	philo = born_philo(data);
	if (!philo)
		return (err_exit(NULL, MEM_ERR));
	threads = born_treads(data, philo);
	if (!threads)
		return (err_exit(data, MEM_ERR * (-1)));
	kill_philo(philo, threads);
	return (0);
}
