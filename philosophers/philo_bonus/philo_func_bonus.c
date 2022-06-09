/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:43:34 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/10 12:01:04 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	gnrl(t_args *data)
{
	int	i;
	int	sig;
	int	*y;

	y = malloc(sizeof(int) * data->number_of_philo);
	ft_memset(y, 0, sizeof(int) * data->number_of_philo);
	i = -1;
	while (++i < data->number_of_philo)
	{
		waitpid(-1, &sig, 0);
		if (!sig)
		{
			i = -1;
			while (++i < data->number_of_philo)
				kill(data->pids[i], SIGTERM);
			break ;
		}
		y[i] = 1;
	}
	i = -1;
	while (++i < data->number_of_philo)
		if (y[i] == 0)
			break ;
	if (!(i != data->number_of_philo))
		printf("All %d philo has finished\n", data->counter);
}

void	chld(t_args *data)
{
	pthread_t	new;

	data->counter++;
	pthread_create(&new, NULL, inspect, data);
	pthread_detach(new);
	if (!(data->counter % 2))
		usleep(500);
	while (data->number_of_eat)
	{
		sem_wait(data->fork);
		ph_writer(data, FORK);
		sem_wait(data->fork);
		ph_writer(data, FORK);
		data->st_eat = cur_ti();
		ph_writer(data, EAT);
		ft_usleep(data->time_to_eat);
		sem_post(data->fork);
		sem_post(data->fork);
		ph_writer(data, SLEEP);
		ft_usleep(data->time_to_sleep);
		ph_writer(data, THINK);
		if (data->number_of_eat != -1)
			data->number_of_eat -= 1;
	}
	exit (1);
}

void	born_philo(t_args *data)
{
	data->counter = 0;
	while (data->counter < data->number_of_philo)
	{
		data->pids[data->counter] = fork();
		if (!data->pids[data->counter])
			break ;
		data->counter++;
	}
}

void	sema_init(int flag, t_args *data)
{
	if (flag == 202)
	{
		sem_unlink("fork");
		sem_unlink("write");
		data->fork = sem_open("fork", O_CREAT, S_IRWXU, data->number_of_philo);
		data->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	}
	else if (flag == 201)
	{
		sem_close(data->fork);
		sem_close(data->write);
		sem_unlink("fork");
		sem_unlink("write");
	}
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
	tmp->st_eat = cur_ti();
	return (tmp);
}
