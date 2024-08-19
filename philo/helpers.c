/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:21:20 by fraqioui          #+#    #+#             */
/*   Updated: 2023/05/31 16:02:47 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

unsigned int	ft_atoi(const char *s)
{
	long long	res;
	long long	prev;

	res = 0;
	while (*s != '\0' && (*s == ' ' || *s == '\n' || *s == '\t'
			||*s == '\f' || *s == '\r' || *s == '\v'))
		s++;
	while (*s >= '0' && *s <= '9')
	{
		prev = res;
		res = res * 10 + (*s - 48);
		if (prev != res / 10)
			return (-1);
		s++;
	}
	return (res);
}

bool	check_valid(char *s)
{
	while (*s != '\0' && (*s == ' ' || *s == '\n' || *s == '\t'
			||*s == '\f' || *s == '\r' || *s == '\v'))
		s++;
	if (!*s)
		return (ft_putstr_fd("Error: Empty argument\n", 2), false);
	if (*s == '+')
		s++;
	else if (*s == '-')
		return (ft_putstr_fd("Error: Negative argument\n", 2), false);
	while (*s >= '0' && *s <= '9')
		s++;
	while (*s != '\0' && (*s == ' ' || *s == '\n' || *s == '\t'
			||*s == '\f' || *s == '\r' || *s == '\v'))
		s++;
	if (*s)
		return (ft_putstr_fd("Error: Numeric argument required\n", 2), false);
	return (true);
}
