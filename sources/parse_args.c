/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:36:41 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/13 18:54:20 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static BOOL	atou_parsing(const char *str, int *nb)
{
	int	i;
	int	tmp;
	int	check;

	if (!str)
		return (FALSE);
	i = 0;
	tmp = 0;
	check = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp *= 10;
		tmp += str[i] - '0';
		i++;
		check++;
		if (tmp < *nb)
			return (FALSE);
		*nb = tmp;
	}
	if (str[i] || !check)
		return (FALSE);
	return (TRUE);
}

static BOOL	mallocing(t_facebook *fb, int max)
{
	fb->philos = malloc(sizeof(t_philo) * max);
	if (!(fb->philos))
		return (FALSE);
	fb->forks = malloc(sizeof(t_fork) * max);
	if (!(fb->forks))
	{
		free(fb->philos);
		return (FALSE);
	}
	return (TRUE);
}

static void	build_list2(t_facebook *fb, t_philo *philo)
{
	philo->is_dead = &(fb->is_end);
	philo->buff = &(fb->buff);
	philo->display = &(fb->display);
	if (fb->nb > 15)
		philo->sleep = usleep;
	else
		philo->sleep = optimized_msleep;
}

static BOOL	build_list(t_facebook *fb, t_philo *philos, int max)
{
	int	i;

	if (!mallocing(fb, max))
		return (error(fb, FALSE, "Malloc error\n", 13));
	philos = fb->philos;
	if (pthread_mutex_init(&(fb->display), NULL) != 0)
		return (error(fb, TRUE, "Mutex init error\n", 17));
	i = -1;
	while (++i < max)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].fb = fb;
		if (pthread_mutex_init(&(fb->forks[i]), NULL) != 0)
			return (error(fb, TRUE, "Mutex init error\n", 17));
		philos[i].fork1 = &(fb->forks[i]);
		if (i + 1 < max)
			philos[i].fork2 = &(fb->forks[i + 1]);
		build_list2(fb, &(philos[i]));
	}
	philos[max - 1].fork2 = &(fb->forks[0]);
	return (TRUE);
}

BOOL	parse_args(t_facebook *fb, char **av, int ac)
{
	if (!atou_parsing(av[0], &(fb->nb)) || !atou_parsing(av[1], &(fb->die))
		|| !atou_parsing(av[2], &(fb->eat))
		|| !atou_parsing(av[3], &(fb->sleep)))
		return (error(fb, FALSE, "Wrong args format\n", 18));
	if (fb->eat > 2147483 || fb->sleep > 2147483)
		return (error(fb, FALSE, "Wrong args format\n", 18));
	if (fb->nb > 15)
	{
		fb->eat *= 1000;
		fb->sleep *= 1000;
	}
	if (ac == 6)
	{
		if (!atou_parsing(av[4], &(fb->meals)))
			return (error(fb, FALSE, "Wrong args format\n", 18));
	}
	else
		fb->meals = 999999999;
	if (fb->nb <= 0)
		return (error(fb, FALSE, "Wrong number of philo\n", 22));
	return (build_list(fb, NULL, fb->nb));
}

//	if (fb->die < 0)
//		return (error(fb, FALSE, "Wrong death timer\n", 18));
//	if (fb->eat < 0)
//		return (error(fb, FALSE, "Wrong eat timer\n", 16));
//	if (fb->sleep < 0)
//		return (error(fb, FALSE, "Wrong sleep timer\n", 18));
