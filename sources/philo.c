/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:58:01 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/27 22:04:34 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	odd_eat(t_facebook *fb, t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(philo->display);
	set_mealtimer(philo, printer(philo, EAT,
			printer(philo, FORK, printer(philo, FORK, -1))));
	pthread_mutex_unlock(philo->display);
	increment_meals(philo);
	philo->sleep(fb->eat);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
}

void	even_eat(t_facebook *fb, t_philo *philo)
{
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->display);
	set_mealtimer(philo, printer(philo, EAT,
			printer(philo, FORK, printer(philo, FORK, -1))));
	pthread_mutex_unlock(philo->display);
	increment_meals(philo);
	philo->sleep(fb->eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	*even_routine(t_philo *philo)
{
	t_facebook	*fb;

	fb = philo->fb;
	if (fb->nb <= 1)
		return (NULL);
	while (!get_fbend(fb))
	{
		even_eat(fb, philo);
		display_status(philo, SLEEP, -1);
		philo->sleep(fb->sleep);
		display_status(philo, THINK, -1);
		usleep(120);
	}
	return (NULL);
}

void	*odd_routine(t_philo *philo)
{
	t_facebook	*fb;

	fb = philo->fb;
	if (fb->nb <= 1)
		return (NULL);
	while (!get_fbend(fb))
	{
		odd_eat(fb, philo);
		display_status(philo, SLEEP, -1);
		philo->sleep(fb->sleep);
		display_status(philo, THINK, -1);
		usleep(120);
	}
	return (NULL);
}
