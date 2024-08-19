/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 08:23:46 by fraqioui          #+#    #+#             */
/*   Updated: 2023/05/31 17:12:28 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

bool	initializing_1(int ac, char **av, t_inputholder *holder)
{
	int	save;
	int	i;

	i = 1;
	save = ac;
	while (--save)
		if (!check_valid(av[i++]))
			return (false);
	holder->init_time = current_time();
	holder->num_philos = ft_atoi(av[1]);
	holder->time_to_die = ft_atoi(av[2]);
	holder->time_to_eat = ft_atoi(av[3]);
	holder->time_to_sleep = ft_atoi(av[4]);
	holder->incre = 0;
	if (ac == 6)
		holder->num_eats = ft_atoi(av[5]);
	else
		holder->num_eats = -1;
	if (!holder->num_eats || !holder->time_to_die || !holder->time_to_eat
		|| !holder->time_to_sleep)
		return (ft_putstr_fd("Error: Zero is invalid\n", 2), false);
	if (pthread_mutex_init(&holder->save_2, NULL)
		|| pthread_mutex_init(&holder->save_1, NULL))
		return (false);
	return (true);
}

pthread_mutex_t	*initializing_2(t_inputholder *holder)
{
	pthread_mutex_t	*save;
	unsigned int	i;

	i = 0;
	save = malloc(sizeof(pthread_mutex_t) * holder->num_philos);
	if (!save)
		return (ft_putstr_fd("allocation failure\n", 2), NULL);
	while (i < holder->num_philos)
		if (pthread_mutex_init(&save[i++], NULL))
			return (free(save), ft_putstr_fd("cannot create mutex\n", 2), NULL);
	return (save);
}

pthread_mutex_t	*initializing_5(t_inputholder *holder)
{
	pthread_mutex_t	*ret;
	unsigned int	i;

	i = 0;
	ret = malloc(sizeof(pthread_mutex_t) * holder->num_philos);
	if (!ret)
		return (ft_putstr_fd("allocation failure\n", 2), NULL);
	while (i < holder->num_philos)
		if (pthread_mutex_init(&ret[i++], NULL))
			return (free(ret), ft_putstr_fd("cannot create mutex\n", 2), NULL);
	return (ret);
}

t_phlthread	*initializing_3(t_inputholder *holder,
pthread_mutex_t *save, pthread_mutex_t *ret)
{
	unsigned int	i;
	t_phlthread		*phls;

	i = 0;
	phls = malloc(sizeof(t_phlthread) * holder->num_philos);
	if (!phls)
		return (free(ret), free(save), free(holder),
			ft_putstr_fd("allocation failure\n", 2), NULL);
	while (i < holder->num_philos)
	{
		phls[i].times_eat = 0;
		if (i == holder->num_philos - 1)
			phls[i].index = 0;
		else
			phls[i].index = i + 1;
		phls[i].pos = i;
		phls[i].place = i + 1;
		phls[i].holder = holder;
		phls[i].fork = save;
		phls[i].eating = ret;
		phls[i].last_time_eat = current_time();
		i++;
	}
	return (phls);
}
