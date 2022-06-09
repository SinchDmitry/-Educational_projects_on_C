/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:51 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/10 11:58:35 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define FORK		11
# define EAT		12
# define SLEEP		13
# define THINK		14
# define DEAD		0
# define ARG_ERR 	100
# define PARSE_ERR 	101
# define MEM_ERR 	102
# define END 		200
# define DELETE 	201
# define OPEN 		202

typedef struct s_args
{
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	int		counter;
	int		pids[210];
	long	st_t;
	long	st_eat;
	int		exit_code;
	sem_t	*fork;
	sem_t	*write;
}	t_args;

int			err_exit(t_args *data, int flag);
int			ft_atoi(const char *str);
void		ft_usleep(int mtime);
long		cur_ti(void);
t_args		*args_init(int argc, char **argv);
void		ft_putnbr(int n);
void		*ft_memset(void *b, int c, size_t len);

void		sema_init(int flag, t_args *data);
void		*inspect(void *philo);
void		ph_writer(t_args *data, int flag);
void		chld(t_args *data);
void		gnrl(t_args *data);
void		born_philo(t_args *data);

#endif