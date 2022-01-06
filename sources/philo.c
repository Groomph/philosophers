/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:58:01 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/13 19:06:37 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	odd_eat(t_facebook *fb, t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(philo->display);
	printer(philo, FORK, -1);
	printer(philo, FORK, -1);
	pthread_mutex_unlock(philo->display);
	philo->last_meal = display_status(philo, EAT, -1);
	philo->meals++;
	philo->sleep(fb->sleep);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
}

void	even_eat(t_facebook *fb, t_philo *philo)
{
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->display);
	printer(philo, FORK, -1);
	printer(philo, FORK, -1);
	pthread_mutex_unlock(philo->display);
	philo->last_meal = display_status(philo, EAT, -1);
	philo->meals++;
	philo->sleep(fb->sleep);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	*even_routine(t_philo *philo)
{
	t_facebook	*fb;

	fb = philo->fb;
	if (fb->nb <= 1)
		return (NULL);
	while (!*(philo->is_dead))
	{
		even_eat(fb, philo);
		display_status(philo, SLEEP, -1);
		philo->sleep(fb->sleep);
		display_status(philo, THINK, -1);
		usleep(100);
	}
	return (NULL);
}

void	*odd_routine(t_philo *philo)
{
	t_facebook	*fb;

	fb = philo->fb;
	if (fb->nb <= 1)
		return (NULL);
	while (!*(philo->is_dead))
	{
		odd_eat(fb, philo);
		display_status(philo, SLEEP, -1);
		philo->sleep(fb->sleep);
		display_status(philo, THINK, -1);
		usleep(100);
	}
	return (NULL);
}
