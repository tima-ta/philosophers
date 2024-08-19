/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:57:33 by fraqioui          #+#    #+#             */
/*   Updated: 2023/05/31 17:12:41 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<unistd.h>
# include<sys/time.h>
# include<pthread.h>
# include<stdbool.h>
# include<stdlib.h>
# include<stdio.h>

typedef struct s_holder
{
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eats;
	unsigned int	num_philos;
	unsigned int	incre;
	unsigned long	init_time;
	pthread_mutex_t	save_2;
	pthread_mutex_t	save_1;
}	t_inputholder;

typedef struct s_phlthread
{
	pthread_t			thread;
	unsigned int		index;
	unsigned int		pos;
	unsigned int		place;
	unsigned int		times_eat;
	unsigned long		last_time_eat;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*eating;
	t_inputholder		*holder;
}	t_phlthread;

void			ft_putstr_fd(char *s, int fd);
unsigned int	ft_atoi(const char *str);
unsigned long	current_time(void);
void			_usleep_(unsigned long time);
void			_mutex_destroy(t_phlthread *phls);
bool			begin_eating(t_phlthread *phls);
void			*thread_routine(void *arg);
void			routine(t_phlthread *phls, unsigned long tm);
bool			check_valid(char *s);
bool			initializing_1(int ac, char **av, t_inputholder *holder);
pthread_mutex_t	*initializing_2(t_inputholder *holder);
pthread_mutex_t	*initializing_5(t_inputholder *holder);
t_phlthread		*initializing_3(t_inputholder *holder,
					pthread_mutex_t *save, pthread_mutex_t *ret);

#endif
