/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:34:04 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 16:27:35 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

static void	launcher(t_facebook *fb, t_philo *philos, int i)
{
	pid_t	pid;

	while (i < fb->nb)
	{
		pid = fork();
		if (pid == 0)
		{
			launch_child(fb, &(philos[i]));
		}
		else if (pid == -1)
			error(NULL, FALSE, "Philo launch failed\n", -1);
		fb->pid[i] = pid;
		i += 2;
	}
}

static void	*count_meals(t_facebook *fb)
{
	int	i;

	i = 0;
	while (i < fb->nb && !(fb->end))
	{
		sem_wait(fb->count_meals);
		i++;
	}
	if (!(fb->end))
		sem_wait(fb->display);
	sem_post(fb->death);
	return (NULL);
}

static void	*wait_death(t_facebook *fb)
{
	sem_wait(fb->death);
	fb->end = TRUE;
	sem_post(fb->count_meals);
	return (NULL);
}

static void	*simulation_starter(t_facebook *fb)
{
	int	i;

	i = 0;
	usleep(2000 * fb->nb);
	while (i < fb->nb)
	{
		sem_post(fb->start);
		i++;
	}
	return (NULL);
}

BOOL	launch_thread(t_facebook *fb, t_philo *philos)
{
	pthread_t	thread;
	pthread_t	thread2;
	pthread_t	thread3;
	int			i;

	launcher(fb, philos, 0);
	launcher(fb, philos, 1);
	safe_thr_create(&thread, (void *)(void *)count_meals, fb);
	safe_thr_create(&thread2, (void *)(void *)wait_death, fb);
	safe_thr_create(&thread3, (void *)(void *)simulation_starter, fb);
	safe_thr_wait(thread3);
	safe_thr_wait(thread2);
	safe_thr_wait(thread);
	i = 0;
	while (i < fb->nb)
	{
		if (fb->pid[i] > 0)
			kill(fb->pid[i], SIGKILL);
		fb->pid[i] = 0;
		i++;
	}
	return (TRUE);
}
