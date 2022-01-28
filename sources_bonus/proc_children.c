/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:34:04 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 15:25:20 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

static void	*monitor_meals(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->fb->meals)
	{
		sem_wait(philo->meals_access);
		i++;
	}
	sem_post(philo->count_meals);
	return (NULL);
}

static void	*monitor_hunger(t_philo *philo)
{
	t_facebook	*fb;
	long int	time;
	int			count;

	count = 0;
	fb = philo->fb;
	while (1)
	{
		sem_wait(philo->timer_access);
		time = get_timestamp();
		if (time - philo->last_meal >= fb->die)
		{
			sem_wait(philo->display);
			printer(philo, DEAD, time);
			sem_post(philo->death);
			sem_wait(philo->display);
		}
		sem_post(philo->timer_access);
	}
	exit(0);
	return (NULL);
}

static BOOL	init_proc(t_philo *philo, pthread_t *thread, pthread_t *thread2)
{
	if (!safe_open(&(philo->count_meals), "count_meals"))
		return (FALSE);
	if (!safe_open(&(philo->forks), "forks_nam_nam"))
		return (FALSE);
	if (!safe_open(&(philo->display), "displayer"))
		return (FALSE);
	if (!safe_open(&(philo->death), "death"))
		return (FALSE);
	if (!safe_open(&(philo->start), "start_simulation"))
		return (FALSE);
	set_sem_name(philo);
	if (!safe_open(&(philo->meals_access), philo->meals_name))
		return (FALSE);
	if (!safe_open(&(philo->timer_access), philo->timer_name))
		return (FALSE);
	if (!safe_thr_create(thread, (void *)(void *)monitor_meals, philo))
		return (FALSE);
	if (!safe_thr_create(thread2, (void *)(void *)monitor_hunger, philo))
		return (FALSE);
	return (TRUE);
}

static void	suicide_proc(t_facebook *fb, t_philo *philo, BOOL display)
{
	safe_close(philo->count_meals);
	safe_close(philo->forks);
	safe_close(philo->start);
	safe_close(philo->meals_access);
	safe_close(philo->timer_access);
	if (fb->pid)
		free(fb->pid);
	sem_wait(philo->display);
	if (display)
		write(2, "ERROR INIT PHILO PROCESS\n", 25);
	sem_post(philo->death);
	safe_close(philo->display);
	safe_close(philo->death);
	if (fb->philos)
		free(fb->philos);
	while (1)
	{
	}
}

void	launch_child(t_facebook *fb, t_philo *philo)
{
	pthread_t	thread;
	pthread_t	thread2;

	if (!init_proc(philo, &thread, &thread2))
		suicide_proc(fb, philo, TRUE);
	sem_wait(philo->start);
	philo->last_meal = get_timestamp();
	philo->start_sim = philo->last_meal;
	sem_post(philo->timer_access);
	philo_routine(fb, philo);
	safe_thr_wait(thread);
	safe_thr_wait(thread2);
	suicide_proc(fb, philo, FALSE);
	exit(0);
}
