/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:43:34 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/09 00:14:24 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_day(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (!(ph->id % 2))
		usleep(800);
	while (ph->number_of_eat)
	{
		pthread_mutex_lock(ph->left_f);
		ph_writer(ph, ph->in_data, FORK);
		pthread_mutex_lock(&ph->right_f);
		ph_writer(ph, ph->in_data, FORK);
		ph->st_eat = cur_ti();
		ph_writer(ph, ph->in_data, EAT);
		ft_usleep(ph->in_data->time_to_eat);
		pthread_mutex_unlock(ph->left_f);
		pthread_mutex_unlock(&ph->right_f);
		ph_writer(ph, ph->in_data, SLEEP);
		ft_usleep(ph->in_data->time_to_sleep);
		ph_writer(ph, ph->in_data, THINK);
		if (ph->number_of_eat != -1)
			ph->number_of_eat -= 1;
	}
	ph->in_data->eat_counter++;
	ph->finish_act = 1;
	return (NULL);
}

t_philo	*born_philo(t_args *data)
{
	t_philo		*ph;
	int			i;

	i = -1;
	ph = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!ph)
		return (NULL);
	while (++i < data->number_of_philo)
	{
		ph[i] = (t_philo){};
		ph[i].id = i + 1;
		ph[i].in_data = data;
		ph[i].number_of_eat = data->number_of_eat;
		ph[i].st_eat = cur_ti();
		pthread_mutex_init(&ph[i].right_f, NULL);
	}
	i = 0;
	while (++i < data->number_of_philo)
		ph[i].left_f = &ph[i - 1].right_f;
	ph[0].left_f = &ph[i - 1].right_f;
	pthread_mutex_init(&ph->in_data->write, NULL);
	return (ph);
}

pthread_t	*born_treads(t_args *data, t_philo *ph)
{
	pthread_t	*th;
	int			th_ok;
	int			i;

	i = -1;
	th = malloc(sizeof(pthread_t) * (data->number_of_philo));
	if (!th)
		err_exit(ph->in_data, -2);
	data->st_t = cur_ti();
	while (++i < data->number_of_philo)
	{
		th_ok = pthread_create(&th[i], NULL, ph_day, &(ph[i]));
		if (th_ok)
			return (NULL);
		pthread_detach(th[i]);
	}
	th_ok = pthread_create(&th[data->number_of_philo], NULL, inspect, ph);
	if (th_ok)
		return (NULL);
	pthread_join(th[data->number_of_philo], NULL);
	return (th);
}

void	kill_philo(t_philo *ph, pthread_t *th)
{
	while (ph->in_data->number_of_philo > 0)
	{
		pthread_mutex_destroy(&ph[ph->in_data->number_of_philo].right_f);
		(ph->in_data->number_of_philo)--;
	}
	pthread_mutex_destroy(&ph->in_data->write);
	free(th);
	free(ph->in_data);
	free(ph);
}
