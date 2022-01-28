/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:38:12 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 15:29:09 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_meals(t_philo *philo)
{
	int	nb;

	pthread_mutex_lock(&(philo->getmeals));
	nb = philo->meals;
	pthread_mutex_unlock(&(philo->getmeals));
	return (nb);
}

void	increment_meals(t_philo *philo)
{
	pthread_mutex_lock(&(philo->getmeals));
	philo->meals++;
	pthread_mutex_unlock(&(philo->getmeals));
}

long int	get_mealtimer(t_philo *philo)
{
	long int	timer;

	pthread_mutex_lock(&(philo->gettimer));
	timer = philo->last_meal;
	pthread_mutex_unlock(&(philo->gettimer));
	return (timer);
}

void	set_mealtimer(t_philo *philo, long int timer)
{
	pthread_mutex_lock(&(philo->gettimer));
	philo->last_meal = timer;
	pthread_mutex_unlock(&(philo->gettimer));
}
