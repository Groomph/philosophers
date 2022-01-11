/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:36:41 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:30:14 by rsanchez         ###   ########.fr       */
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

static BOOL	build_list(t_facebook *fb, t_philo *philos, int max)
{
	int	i;

	fb->philos = malloc(sizeof(t_philo) * max);
	if (!(fb->philos))
		return (error(fb, FALSE, "Malloc error\n", 13));
	philos = fb->philos;
	i = -1;
	while (++i < max)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].fb = fb;
		philos[i].is_dead = FALSE;
		if (fb->nb > 15)
			philos[i].sleep = usleep;
		else
			philos[i].sleep = optimized_msleep;
	}
	fb->pid = malloc(sizeof(pid_t) * max);
	if (!(fb->pid))
		return (error(NULL, FALSE, "malloc pid array", -1));
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
