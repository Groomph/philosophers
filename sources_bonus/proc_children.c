/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:34:04 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:23:39 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>

static void	*monitoring(t_philo *philo)
{
	t_facebook	*fb;
	long int	time;
	int			count;

	count = 0;
	fb = philo->fb;
	while (1)
	{
		time = get_timestamp();
		if (time - philo->last_meal >= fb->die)
		{
			sem_wait(philo->display);
			philo->is_dead = TRUE;
			printer(philo, DEAD, time);
			sem_post(philo->death);
			sem_wait(philo->display);
		}
		if (philo->meals >= fb->meals && count++ == 0)
			sem_post(philo->count_meals);
	}
	exit(0);
	return (NULL);
}

void	launch_child(t_facebook *fb, t_philo *philo)
{
	pthread_t	thread;

	safe_open(&(philo->forks), "forks_nam_nam");
	safe_open(&(philo->display), "displayer");
	safe_open(&(philo->count_meals), "count_meals");
	safe_open(&(philo->death), "death");
	safe_open(&(philo->start), "start_simulation");
	sem_wait(philo->start);
	philo->last_meal = get_timestamp();
	safe_thr_create(&thread, (void *)(void *)monitoring, philo);
	philo_routine(fb, philo);
	safe_thr_wait(thread);
	safe_close(philo->count_meals);
	safe_close(philo->forks);
	safe_close(philo->display);
	safe_close(philo->death);
	safe_close(philo->start);
	free(fb->philos);
	free(fb->pid);
	exit(0);
}
