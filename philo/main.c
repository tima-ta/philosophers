/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:56:28 by fraqioui          #+#    #+#             */
/*   Updated: 2023/05/31 17:13:12 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static t_phlthread	*initializing_help(int ac, char **av)
{
	t_inputholder	*holder;
	pthread_mutex_t	*save;
	pthread_mutex_t	*ret;

	holder = malloc(sizeof(t_inputholder));
	if (!holder)
		return (ft_putstr_fd("allocation failure\n", 2), NULL);
	if (!initializing_1(ac, av, holder))
		return (free(holder), NULL);
	save = initializing_2(holder);
	if (!save)
		return (free(holder), NULL);
	ret = initializing_5(holder);
	if (!ret)
		return (free(save), free(holder), NULL);
	return (initializing_3(holder, save, ret));
}

static t_phlthread	*initializing(int ac, char **av)
{
	t_phlthread		*phls;

	phls = initializing_help(ac, av);
	if (!phls)
		return (NULL);
	return (phls);
}

static	bool	evolve(int ac, char **av)
{
	t_phlthread	*phls;
	bool		check;

	phls = initializing(ac, av);
	if (!phls)
		return (false);
	check = begin_eating(phls);
	if (!check)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6)
	{
		if (!evolve(ac, av))
			return (1);
	}
	else
		ft_putstr_fd("Invalid number of arguments\n", 2);
}
