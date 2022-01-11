/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:58:01 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:33:10 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>
#include <unistd.h>

static void	philo_eat(t_facebook *fb, t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->forks);
	sem_wait(philo->display);
	printer(philo, FORK, printer(philo, FORK, -1));
	sem_post(philo->display);
	philo->last_meal = display_status(philo, EAT, -1);
	philo->meals++;
	philo->sleep(fb->sleep);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	philo_routine(t_facebook *fb, t_philo *philo)
{
	while (1)
	{
		philo_eat(fb, philo);
		display_status(philo, SLEEP, -1);
		philo->sleep(fb->sleep);
		display_status(philo, THINK, -1);
		usleep(100);
	}
}
