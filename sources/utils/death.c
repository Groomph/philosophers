/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:38:12 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 15:29:27 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philoend(t_philo *philo, BOOL end)
{
	pthread_mutex_lock(philo->checkend);
	*(philo->is_dead) = end;
	pthread_mutex_unlock(philo->checkend);
}

BOOL	get_philoend(t_philo *philo)
{
	BOOL	end;

	pthread_mutex_lock(philo->checkend);
	end = *(philo->is_dead);
	pthread_mutex_unlock(philo->checkend);
	return (end);
}

void	set_fbend(t_facebook *fb, BOOL end)
{
	pthread_mutex_lock(&(fb->checkend));
	fb->is_end = end;
	pthread_mutex_unlock(&(fb->checkend));
}

BOOL	get_fbend(t_facebook *fb)
{
	BOOL	end;

	pthread_mutex_lock(&(fb->checkend));
	end = fb->is_end;
	pthread_mutex_unlock(&(fb->checkend));
	return (end);
}
