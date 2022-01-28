/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:34:04 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/27 23:05:19 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "buffer.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

static void	*monitoring(t_philo *philos)
{
	int			i;
	t_facebook	*fb;
	long int	time;
	int			count;

	i = 0;
	fb = philos[0].fb;
	count = 0;
	while (!get_fbend(fb))
	{
		time = get_timestamp();
		if (time - get_mealtimer(&(philos[i])) >= fb->die)
		{
			set_fbend(fb, TRUE);
			display_status(&(philos[i]), DEAD, time);
		}
		if (get_meals(&(philos[i])) >= fb->meals && ++count == fb->nb)
			set_fbend(fb, TRUE);
		else if (++i == fb->nb)
		{
			i = 0;
			count = 0;
		}
	}
	return (NULL);
}

static void	launcher(t_philo *philos, int i, int max, void *(f)(void *))
{
	while (i < max)
	{
		if (pthread_create(&(philos[i].thread), NULL,
				f, &(philos[i])) != 0)
			error(NULL, FALSE, "Philo launch failed\n", 20);
		i += 2;
	}
}

BOOL	launch_thread(t_facebook *fb, t_philo *philos)
{
	int			i;

	i = -1;
	fb->start = get_timestamp();
	if (fb->start < 0)
		return (error(NULL, FALSE, "monitoring", -1));
	while (++i < fb->nb)
		philos[i].last_meal = fb->start;
	launcher(philos, 0, fb->nb, (void *)(void *)odd_routine);
	launcher(philos, 1, fb->nb, (void *)(void *)even_routine);
	if (pthread_create(&(fb->thread), NULL,
			(void *)(void *)monitoring, fb->philos) != 0)
		error(NULL, FALSE, "Philo launch failed\n", 20);
	if (pthread_join(fb->thread, NULL) != 0)
		error(NULL, FALSE, "Thread join failed\n", 19);
	i = 0;
	while (i < fb->nb)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			error(NULL, FALSE, "Thread join failed\n", 19);
		i++;
	}
	print_buffer(&(fb->buff), 1);
	return (TRUE);
}
