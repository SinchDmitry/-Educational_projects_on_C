/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:47 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/10 11:58:23 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*tmp;

	tmp = b;
	i = 0;
	while (i < len)
	{
		tmp[i] = (char)c;
		i++;
	}
	return (b);
}

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

void	*inspect(void *data)
{
	t_args	*ph;

	ph = (t_args *)data;
	while (1)
	{
		if ((cur_ti() - ph->st_eat) > (ph->time_to_die))
		{
			sem_wait(ph->write);
			printf("%ld %d died\n", cur_ti() - ph->st_t, ph->counter);
			exit (0);
		}
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	t_args		*data;

	if (argc > 6 || argc < 5)
		return (err_exit(NULL, ARG_ERR));
	data = args_init(argc, argv);
	if (!data)
		return (err_exit(NULL, PARSE_ERR));
	sema_init(OPEN, data);
	born_philo(data);
	data->st_t = cur_ti();
	if (data->counter == data->number_of_philo)
		gnrl(data);
	else
		chld(data);
	sema_init(DELETE, data);
	return (0);
}
