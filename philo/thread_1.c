/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:08 by fraqioui          #+#    #+#             */
/*   Updated: 2023/05/31 17:11:22 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	bool	death_hlp(t_phlthread *pth, unsigned int i)
{
	pthread_mutex_lock(&pth[i].eating[pth[i].pos]);
	if ((current_time() - pth[i].last_time_eat)
		> pth[i].holder->time_to_die)
	{
		pthread_mutex_lock(&pth[i].holder->save_2);
		printf("%lums %d died\n", current_time() - pth[i].holder->init_time,
			pth[i].place);
		(_mutex_destroy(pth), free(pth->fork),
			free(pth->holder), free(pth));
		return (false);
	}
	pthread_mutex_unlock(&pth[i].eating[pth[i].pos]);
	return (true);
}

static bool	philo_death(t_phlthread *pth)
{
	unsigned int	i;

	i = 0;
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&pth[i].holder->save_1);
		if (pth[i].holder->num_philos == pth[i].holder->incre)
		{
			pthread_mutex_lock(&pth[i].holder->save_2);
			(_mutex_destroy(pth), free(pth->fork),
				free(pth->holder), free(pth));
			return (true);
		}
		pthread_mutex_unlock(&pth[i].holder->save_1);
		if (!death_hlp(pth, i))
			return (false);
		if (i == pth[i].holder->num_philos - 1)
			i = 0;
		else
			i++;
	}
	return (true);
}

void	routine(t_phlthread *phls, unsigned long tm)
{
	pthread_mutex_lock(&phls->fork[phls->pos]);
	pthread_mutex_lock(&phls->holder->save_2);
	printf("%lums %u has taken a fork\n", current_time() - tm, phls->place);
	pthread_mutex_unlock(&phls->holder->save_2);
	pthread_mutex_lock(&phls->fork[phls->index]);
	pthread_mutex_lock(&phls->holder->save_2);
	printf("%lums %u has taken a fork\n", current_time() - tm, phls->place);
	pthread_mutex_unlock(&phls->holder->save_2);
	pthread_mutex_lock(&phls->eating[phls->pos]);
	phls->last_time_eat = current_time();
	pthread_mutex_unlock(&phls->eating[phls->pos]);
	pthread_mutex_lock(&phls->holder->save_1);
	phls->times_eat += 1;
	if (phls->times_eat == phls->holder->num_eats)
		phls->holder->incre++;
	pthread_mutex_unlock(&phls->holder->save_1);
	pthread_mutex_lock(&phls->holder->save_2);
	printf("%lums %u is eating\n", current_time() - tm, phls->place);
	pthread_mutex_unlock(&phls->holder->save_2);
	_usleep_(phls->holder->time_to_eat);
	pthread_mutex_unlock(&phls->fork[phls->pos]);
	pthread_mutex_unlock(&phls->fork[phls->index]);
}

void	*thread_routine(void *arg)
{
	t_phlthread		*phls;
	unsigned long	tm;

	phls = (t_phlthread *)arg;
	pthread_mutex_lock(&phls->eating[phls->pos]);
	phls->last_time_eat = current_time();
	pthread_mutex_unlock(&phls->eating[phls->pos]);
	tm = phls->holder->init_time;
	if (!(phls->index % 2))
		usleep(100);
	while (1)
	{
		routine(phls, tm);
		pthread_mutex_lock(&phls->holder->save_2);
		printf("%lums %u is sleeping\n", current_time() - tm, phls->place);
		pthread_mutex_unlock(&phls->holder->save_2);
		_usleep_(phls->holder->time_to_sleep);
		pthread_mutex_lock(&phls->holder->save_2);
		printf("%lums %u is thinking\n", current_time() - tm, phls->place);
		pthread_mutex_unlock(&phls->holder->save_2);
	}
}

bool	begin_eating(t_phlthread *phls)
{
	unsigned int	i;

	i = 0;
	while (i < phls->holder->num_philos)
	{
		if (pthread_create(&phls[i].thread, NULL, &thread_routine, &phls[i]))
			return (_mutex_destroy(phls), free(phls->holder), free(phls),
				false);
		if (pthread_detach(phls[i].thread))
			return (_mutex_destroy(phls), free(phls->holder), free(phls),
				false);
		i++;
	}
	if (!philo_death(phls))
		return (false);
	return (true);
}
