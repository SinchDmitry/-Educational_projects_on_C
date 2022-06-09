/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:51 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/09 16:00:29 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define FORK		11
# define EAT		12
# define SLEEP		13
# define THINK		14
# define DEAD		15
# define ARG_ERR 	100
# define PARSE_ERR 	101
# define MEM_ERR 	102

typedef struct s_args
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_eat;
	long				st_t;
	int					eat_counter;
	int					exit_code;
	pthread_mutex_t		write;
}	t_args;

typedef struct s_philo
{
	t_args				*in_data;
	pthread_mutex_t		*left_f;
	pthread_mutex_t		right_f;
	int					finish_act;
	int					id;
	int					eat_iter;
	long				st_eat;
	int					number_of_eat;
}	t_philo;

int			err_exit(t_args *data, int flag);
int			ft_atoi(const char *str);
void		ft_usleep(int mtime);
long		cur_ti(void);
t_args		*args_init(int argc, char **argv);

void		*ph_day(void *ph);
void		ph_writer(t_philo *ph, t_args *data, int flag);
t_philo		*born_philo(t_args *data);
pthread_t	*born_treads(t_args *data, t_philo *ph);
void		kill_philo(t_philo *ph, pthread_t *th);

void		*inspect(void *ph);
void		ft_putnbr(int n);
#endif