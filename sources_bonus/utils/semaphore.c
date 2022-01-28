/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:18:05 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 15:38:59 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

BOOL	safe_create(sem_t **sem, char *name, int value)
{
	*sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
	if (*sem == SEM_FAILED)
		return (error(NULL, FALSE, name, -1));
	return (TRUE);
}

BOOL	safe_open(sem_t **sem, char *name)
{
	*sem = sem_open(name, O_RDWR);
	if (*sem == SEM_FAILED)
		return (error(NULL, FALSE, name, -1));
	return (TRUE);
}

BOOL	safe_close(sem_t *sem)
{
	if (sem_close(sem) == -1)
		return (error(NULL, FALSE, "close semaphore", -1));
	return (TRUE);
}

static BOOL	init_philo_sem(int nb)
{
	t_philo	tmp;
	sem_t	*sem;

	tmp.id = 1;
	while (tmp.id <= nb)
	{
		set_sem_name(&tmp);
		sem_unlink(tmp.timer_name);
		if (!safe_create(&sem, tmp.timer_name, 0) || !safe_close(sem))
			return (FALSE);
		sem_unlink(tmp.meals_name);
		if (!safe_create(&sem, tmp.meals_name, 0) || !safe_close(sem))
			return (FALSE);
		tmp.id++;
	}
	return (TRUE);
}

BOOL	init_sem(t_facebook *fb, int forks)
{
	sem_t	*sem;

	sem_unlink("forks_nam_nam");
	sem_unlink("displayer");
	sem_unlink("count_meals");
	sem_unlink("death");
	sem_unlink("start_simulation");
	clean_philo_sem(forks);
	if (!safe_create(&sem, "forks_nam_nam", forks) || !safe_close(sem))
		return (FALSE);
	if (!safe_create(&(fb->display), "displayer", 1))
		return (FALSE);
	if (!safe_create(&(fb->count_meals), "count_meals", 0))
		return (FALSE);
	if (!safe_create(&(fb->death), "death", 0))
		return (FALSE);
	if (!safe_create(&(fb->start), "start_simulation", 0))
		return (FALSE);
	return (init_philo_sem(forks));
}
