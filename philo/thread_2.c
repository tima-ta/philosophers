/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:19 by fraqioui          #+#    #+#             */
/*   Updated: 2023/05/31 17:11:37 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	_mutex_destroy(t_phlthread *phls)
{
	unsigned int	i;

	i = -1;
	pthread_mutex_destroy(&phls->holder->save_2);
	while (++i < phls->holder->num_philos)
		pthread_mutex_destroy(&phls[0].fork[i]);
	i = -1;
	while (++i < phls->holder->num_philos)
		pthread_mutex_destroy(&phls[0].eating[i]);
}

unsigned long	current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	_usleep_(unsigned long time)
{
	unsigned long	c_time;

	c_time = current_time();
	while (current_time() < time + c_time)
		usleep(100);
}
